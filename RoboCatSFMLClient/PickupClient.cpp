#include "RoboCatClientPCH.hpp"

PickupClient::PickupClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture(ETextures::kAmmoRefill));
}

void PickupClient::Read(InputMemoryBitStream& inInputStream)
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
	if (stateBit)
	{
		int category;
		inInputStream.Read(category);
		SetCategory(static_cast<Category>(category));
	}
}

void PickupClient::SetCategory(Category category)
{
	Pickup::SetCategory(category);

	switch (category)
	{
	case kFireRate:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture(ETextures::kFireRate));
		break;
	case kHealthUp:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture(ETextures::kHealthRefill));
		break;
	case kProjectileDamage:
		mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture(ETextures::kAmmoRefill));
		break;
	}
}

