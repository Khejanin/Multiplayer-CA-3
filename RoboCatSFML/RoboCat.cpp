#include "RoboCatPCH.hpp"

RoboCat::RoboCat() :
	DynamicGameObject(),
	mMaxRotationSpeed(100.f),
	mMaxLinearSpeed(5000.f),
	mVelocity(Vector3::Zero),
	mWallRestitution(0.1f),
	mCatRestitution(0.1f),
	mThrustDir(0.f),
	mPlayerId(0),
	mIsShooting(false),
	mHealth(10)
{
	SetSize(Vector3(50, 50, 0));
	SetCanCollide(true);
}

void RoboCat::ProcessInput(float inDeltaTime, const InputState& inInputState)
{
	//process our input....

	//turning...
	float newRotation = GetRotation() + inInputState.GetDesiredHorizontalDelta() * mMaxRotationSpeed * inDeltaTime;
	SetRotation(newRotation);

	//moving...
	float inputForwardDelta = inInputState.GetDesiredVerticalDelta();
	mThrustDir = inputForwardDelta;


	mIsShooting = inInputState.IsShooting();

}

void RoboCat::AdjustVelocityByThrust(float inDeltaTime)
{
	//just set the velocity based on the thrust direction -- no thrust will lead to 0 velocity
	//simulating acceleration makes the client prediction a bit more complex
	Vector3 forwardVector = GetForwardVector();
	mVelocity = forwardVector * (mThrustDir * inDeltaTime * mMaxLinearSpeed);
}

void RoboCat::SimulateMovement(float inDeltaTime)
{
	//simulate us...
	AdjustVelocityByThrust(inDeltaTime);
	
	SetPosition(GetPosition() + mVelocity * inDeltaTime);

	ProcessCollisions();
}

void RoboCat::Update()
{

}

uint32_t RoboCat::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & ECRS_PlayerId)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetPlayerId());

		writtenState |= ECRS_PlayerId;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}


	if (inDirtyState & ECRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 velocity = mVelocity;
		inOutputStream.Write(velocity.mX);
		inOutputStream.Write(velocity.mY);

		Vector3 location = GetPosition();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		inOutputStream.Write(GetRotation());

		writtenState |= ECRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	//always write mThrustDir- it's just two bits
	if (mThrustDir != 0.f)
	{
		inOutputStream.Write(true);
		inOutputStream.Write(mThrustDir > 0.f);
	}
	else
	{
		inOutputStream.Write(false);
	}

	if (inDirtyState & ECRS_Color)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(GetColor());

		writtenState |= ECRS_Color;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & ECRS_Health)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(mHealth, 4);

		writtenState |= ECRS_Health;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	return writtenState;


}



