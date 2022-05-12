#include "RoboCatServerPCH.hpp"

ProjectileServer::ProjectileServer()
{
	//projectile lives five seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 1.0f;
}

void ProjectileServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

void ProjectileServer::Update()
{
	float deltaTime = Timing::sInstance.GetDeltaTime();

	auto x = mVelocity.mX;
	auto y = mVelocity.mY;
	LOG("Projectile Velocity X: %f Y: %f", x, y)

	SetPosition(GetPosition() + mVelocity * deltaTime);

	NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), EPRS_Pose);

	LOG("Projectile Position X: %f Y: %f", GetPosition().mX, GetPosition().mY)

	ProcessCollisions();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
}

bool ProjectileServer::HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo)
{
	switch (inDynGo->GetClassId())
	{
	case 'TANK':
		{
			Tank* tank = dynamic_cast<Tank*>(inDynGo);
			if (tank->GetPlayerId() != GetPlayerId())
			{
				//kill yourself!
				SetDoesWantToDie(true);

				dynamic_cast<TankServer*>(tank)->TakeDamage(GetPlayerId(), 10);
			}
		}
		break;
	}

	return false;
}
