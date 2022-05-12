#include "RoboCatPCH.hpp"

DynamicGameObject::DynamicGameObject()
	:mVelocity(Vector3::Zero),
	mWallRestitution(0.1f),
	mDynGoRestitution(0.1f),
	mCollidesWithWorldBounds(true)
{
}

void DynamicGameObject::ProcessCollisions()
{
	//right now just bounce off the sides..
	if(mCollidesWithWorldBounds) ProcessCollisionsWithWorldBounds();

	auto sourceBounds = GetBounds();
	auto sourcePosition = GetPosition();
	float sourceRadius = std::sqrtf(std::powf(sourceBounds.width, 2) + std::powf(sourceBounds.height, 2));

	//now let's iterate through the world and see what we hit...
	//note: since there's a small number of objects in our game, this is fine.
	//but in a real game, brute-force checking collisions against every other object is not efficient.
	//it would be preferable to use a quad tree or some other structure to minimize the
	//number of collisions that need to be tested.
	for (auto goIt = World::sInstance->GetGameObjects().begin(), end = World::sInstance->GetGameObjects().end(); goIt != end; ++goIt)
	{
		GameObject* target = goIt->get();
		if (target != this && !target->DoesWantToDie())
		{
			auto targetBounds = target->GetBounds();
			bool collide = sourceBounds.intersects(targetBounds);
			
			if (collide)
			{
				//first, tell the other guy there was a collision with a cat, so it can do something...

				bool blocking = false;

				if (this->GetPriority() > target->GetPriority())
				{
					blocking = HandleCollisionWithDynamicGameObject(this);
				}
				else
				{
					blocking = target->HandleCollisionWithDynamicGameObject(this);
				}

				if (blocking)
				{
					auto targetPosition = target->GetPosition();
					auto delta = targetPosition - sourcePosition;
					float targetRadius = std::sqrtf(std::powf(targetBounds.width, 1) + std::powf(targetBounds.height, 1));
					auto collisionDist = sourceRadius + targetRadius;

					//okay, you hit something!
					//so, project your location far enough that you're not colliding
					Vector3 dirToTarget = delta;
					dirToTarget.Normalize2D();
					Vector3 acceptableDeltaFromSourceToTarget = dirToTarget * collisionDist;
					//important note- we only move this cat. the other cat can take care of moving itself

					SetPosition(targetPosition - acceptableDeltaFromSourceToTarget);

					Vector3 relVel = mVelocity;

					//if other object is a dynamic GO, it might have velocity, so there might be relative velocity...
					DynamicGameObject* targetDynGo = target->GetAsDynamicGameObject();
					if (targetDynGo)
					{
						relVel -= targetDynGo->mVelocity;
					}

					//got vel with dir between objects to figure out if they're moving towards each other
					//and if so, the magnitude of the impulse ( since they're both just balls )
					float relVelDotDir = Dot2D(relVel, dirToTarget);

					if (relVelDotDir > 0.f)
					{
						Vector3 impulse = relVelDotDir * dirToTarget;

						if (targetDynGo)
						{
							mVelocity -= impulse;
							mVelocity *= mDynGoRestitution;
						}
						else
						{
							mVelocity -= impulse * 2.f;
							mVelocity *= mWallRestitution;
						}

					}
					
				}
			}
		}
	}

}

void DynamicGameObject::ProcessCollisionsWithWorldBounds()
{
	Vector3 location = GetPosition();
	float x = location.mX;
	float y = location.mY;

	float vx = mVelocity.mX;
	float vy = mVelocity.mY;

	auto bounds = GetBounds();
	auto boundsXHalf = bounds.width / 2.f;
	auto boundsYHalf = bounds.height / 2.f;

	//if the object collides against a wall, the quick solution is to push it off
	if ((y + boundsYHalf) >= WORLD_HEIGHT && vy > 0)
	{
		mVelocity.mY = -vy * mWallRestitution;
		location.mY = WORLD_HEIGHT - boundsYHalf;
		SetPosition(location);
	}
	else if ((y - boundsYHalf) <= 0 && vy < 0)
	{
		mVelocity.mY = -vy * mWallRestitution;
		location.mY = boundsYHalf;
		SetPosition(location);
	}

	if ((x + boundsXHalf) >= WORLD_WIDTH && vx > 0)
	{
		mVelocity.mX = -vx * mWallRestitution;
		location.mX = WORLD_WIDTH - boundsXHalf;
		SetPosition(location);
	}
	else if ((x - boundsXHalf) <= 0 && vx < 0)
	{
		mVelocity.mX = -vx * mWallRestitution;
		location.mX = boundsXHalf;
		SetPosition(location);
	}
}
