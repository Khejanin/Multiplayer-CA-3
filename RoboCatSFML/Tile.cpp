#include "RoboCatPCH.hpp"

Tile::Tile()
	: mHealth(10)
{
	SetSize(Vector3(10, 10, 0));
	SetScale(5);
}

uint32_t Tile::Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const
{
	uint32_t writtenState = 0;

	if (inDirtyState & Tile::ETRS_Pose)
	{
		inOutputStream.Write((bool)true);

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

	if (inDirtyState & Tile::ETRS_Tex)
	{
		inOutputStream.Write((bool)true);
		inOutputStream.Write(mTexId);
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	return writtenState;
}

void Tile::Update()
{
	GameObject::Update();
}

bool Tile::HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo)
{
	return true;
}

void Tile::SetTexId(int texId)
{
	mTexId = texId;
}

int Tile::GetTexId() const
{
	return mTexId;
}
