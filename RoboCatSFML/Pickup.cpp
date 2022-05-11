#include "RoboCatPCH.hpp"

Pickup::Pickup()
{
	SetSize(Vector3(40, 40,0));
}

uint32_t Pickup::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & Pickup::EPRS_Pose)
	{
		inOutputStream.Write((bool)true);

		Vector3 location = GetPosition();
		inOutputStream.Write(location.mX);
		inOutputStream.Write(location.mY);

		writtenState |= EPRS_Pose;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	if (inDirtyState & Pickup::EPRS_Type)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(mCategory);

		writtenState |= EPRS_Type;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	return writtenState;
}

bool Pickup::HandleCollisionWithDynamicGameObject(DynamicGameObject* in_dyn_go)
{
	return false;
}

void Pickup::SetCategory(Category category)
{
	mCategory = category;
}

Pickup::Category Pickup::GetCategory() const
{
	return mCategory;
}