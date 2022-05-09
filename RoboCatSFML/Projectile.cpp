#include "RoboCatPCH.hpp"

Projectile::Projectile() :
	mMuzzleSpeed(300.f),
	mVelocity(Vector3::Zero),
	mPlayerId(0)
{
	SetSize(Vector3(3, 14, 0));
}

uint32_t Projectile::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & EPRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 location = GetPosition();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		Vector3 velocity = GetVelocity();
		inOutputStream.Write(velocity.mX);
		inOutputStream.Write(velocity.mY);

		inOutputStream.Write(GetRotation());

		writtenState |= EPRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & EPRS_Color)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(GetColor());

		writtenState |= EPRS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & EPRS_PlayerId)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(mPlayerId, 8);

		writtenState |= EPRS_PlayerId;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}
	return writtenState;
}

void Projectile::InitFromShooter(Tank* inShooter)
{
	SetColor(inShooter->GetColor());
	SetPlayerId(inShooter->GetPlayerId());

	Vector3 forward = inShooter->GetForwardVector();
	SetVelocity(inShooter->GetVelocity() + forward * mMuzzleSpeed);
	SetPosition(inShooter->GetPosition() /* + forward * 0.55f */);

	SetRotation(inShooter->GetRotation());
}

void Projectile::Update()
{
	float deltaTime = Timing::sInstance.GetDeltaTime();

	SetPosition(GetPosition() + mVelocity * deltaTime);

	//we'll let the tanks handle the collisions
}

bool Projectile::HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo)
{
	(void)inDynGo;

	return false;
}
