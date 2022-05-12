#include "RoboCatPCH.hpp"

Projectile::Projectile() :
	DynamicGameObject(),
	mMuzzleSpeed(500.f),
	mPlayerId(0),
	mDoubleDamage(false)
{
	mCollidesWithWorldBounds = false;
	SetSize(Vector3(14, 14, 0));
	SetPriority(1);
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

void Projectile::InitFromShooter(Tank* inShooter, bool doubleDamage)
{
	mDoubleDamage = doubleDamage;
	SetColor(inShooter->GetColor());
	SetPlayerId(inShooter->GetPlayerId());

	Vector3 forward = inShooter->GetForwardVector();
	SetVelocity(forward * mMuzzleSpeed);
	SetPosition(inShooter->GetPosition() + forward * 20.0f);

	SetRotation(inShooter->GetRotation());
}

void Projectile::Update()
{
}

bool Projectile::HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo)
{
	(void)inDynGo;

	return false;
}
