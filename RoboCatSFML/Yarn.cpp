#include "RoboCatPCH.hpp"

Yarn::Yarn() :
	mMuzzleSpeed(300.f),
	mVelocity(Vector3::Zero),
	mPlayerId(0)
{
	SetScale(GetScale() * 0.25f);
	SetSize(Vector3(20, 20, 0));
}


uint32_t Yarn::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & EYRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 location = GetPosition();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		Vector3 velocity = GetVelocity();
		inOutputStream.Write(velocity.mX);
		inOutputStream.Write(velocity.mY);

		inOutputStream.Write(GetRotation());

		writtenState |= EYRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & EYRS_Color)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(GetColor());

		writtenState |= EYRS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & EYRS_PlayerId)
	{
		inOutputStream.Write((bool)true);

		inOutputStream.Write(mPlayerId, 8);

		writtenState |= EYRS_PlayerId;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}
	return writtenState;
}


bool Yarn::HandleCollisionWithDynamicGameObject(DynamicGameObject* inCat)
{
	(void)inCat;

	//you hit a cat, so look like you hit a cat
	return false;
}


void Yarn::InitFromShooter(RoboCat* inShooter)
{
	SetColor(inShooter->GetColor());
	SetPlayerId(inShooter->GetPlayerId());

	Vector3 forward = inShooter->GetForwardVector();
	SetVelocity(inShooter->GetVelocity() + forward * mMuzzleSpeed);
	SetPosition(inShooter->GetPosition() /* + forward * 0.55f */);

	SetRotation(inShooter->GetRotation());
}

void Yarn::Update()
{
	float deltaTime = Timing::sInstance.GetDeltaTime();

	SetPosition(GetPosition() + mVelocity * deltaTime);


	//we'll let the cats handle the collisions
}
