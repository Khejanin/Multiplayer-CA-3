#include "RoboCatPCH.hpp"

Tank::Tank() :
	DynamicGameObject(),
	mMaxLinearSpeed(5000.f),
	mVelocity(Vector3::Zero),
	mWallRestitution(0.1f),
	mCatRestitution(0.1f),
	mPlayerId(0),
	mIsShooting(false),
	mHealth(10)
{
	SetScale(5);
	SetSize(Vector3(10, 10, 0));
	SetCanCollide(true);
}

void Tank::Update()
{
}

void Tank::ProcessInput(float inDeltaTime, const InputState& inInputState)
{
	auto accDir = Vector3(inInputState.GetDesiredHorizontalDelta(), -inInputState.GetDesiredVerticalDelta(), 0);
	mIsShooting = inInputState.IsShooting();
	mIsThrusting = accDir.Length() > 0;
	if(mIsThrusting)
		SetRotation(RoboMath::ToDegrees(std::atan2(accDir.mY, accDir.mX)) + 90);
}

void Tank::SimulateMovement(float inDeltaTime)
{
	//simulate us...
	AdjustVelocityByThrust(inDeltaTime);

	SetPosition(GetPosition() + mVelocity * inDeltaTime);

	ProcessCollisions();
}

void Tank::AdjustVelocityByThrust(float inDeltaTime)
{
	//just set the velocity based on the thrust direction -- no thrust will lead to 0 velocity
	//simulating acceleration makes the client prediction a bit more complex
	if (!mIsThrusting) 
	{
		mVelocity = Vector3::Zero;
		return;
	}

	Vector3 forwardVector = GetForwardVector();
	mVelocity = forwardVector * (inDeltaTime * mMaxLinearSpeed);
}

uint32_t Tank::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & ETRS_PlayerId)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetPlayerId());

		writtenState |= ETRS_PlayerId;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}


	if (inDirtyState & ETRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 velocity = mVelocity;
		inOutputStream.Write(velocity.mX);
		inOutputStream.Write(velocity.mY);

		Vector3 location = GetPosition();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		inOutputStream.Write(GetRotation());

		writtenState |= ETRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	inOutputStream.Write(mIsThrusting);

	if (inDirtyState & ETRS_Color)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetColor());

		writtenState |= ETRS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ETRS_Health)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(mHealth, 4);

		writtenState |= ETRS_Health;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	return writtenState;


}
