#include "RoboCatClientPCH.hpp"

TileClient::TileClient() : Tile()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture(ETextures::kTileUpRight));
}

void TileClient::Read(InputMemoryBitStream& inInputStream)
{
	bool stateBit;

	inInputStream.Read(stateBit);
	if (stateBit)
	{
		Vector3 location;
		inInputStream.Read(location.mX);
		inInputStream.Read(location.mY);
		SetPosition(location);
	}

	inInputStream.Read(stateBit);
	if(stateBit)
	{
		int texId;
		inInputStream.Read(texId);
		SetTexId(texId);
	}
}

void TileClient::SetTexId(int texId)
{
	Tile::SetTexId(texId);

	//Hard coded switch case, too much work to do it properly
	ETextures tex;
	switch (texId)
	{
	case 80:
		tex = ETextures::kTileUpLeft;
		break;
	case 81:
		tex = ETextures::kTileUpRight;
		break;
	case 96:
		tex = ETextures::kTileDownLeft;
		break;
	case 97:
		tex = ETextures::kTileDownRight;
		break;
	default:
		//Break it if you get something unexpected
		tex = ETextures::kExplosion;
		break;
	}

	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture(tex));
}

