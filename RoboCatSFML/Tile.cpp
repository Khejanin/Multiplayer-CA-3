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

		writtenState |= ETRS_Tex;
	}
	else
	{
		inOutputStream.Write((bool)false);
	}

	return writtenState;
}

bool Tile::HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo)
{
	switch (inDynGo->GetClassId())
	{
	case 'PROJ':
	{
		Projectile* proj = dynamic_cast<Projectile*>(inDynGo);

		//projectile dies!
		proj->SetDoesWantToDie(true);
		return false;
	}
	break;
	}
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
