#include "RoboCatClientPCH.hpp"

Explosion::Explosion() :
	mAnimation(*TextureManager::sInstance->GetTexture(ETextures::kExplosion)),
	mTTL(1)
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture(ETextures::kExplosion));
	mAnimation.SetFrameSize(sf::Vector2i(256, 256));
	mAnimation.SetNumFrames(16);
	mAnimation.SetDuration(1);
}

void Explosion::Update()
{
	float dt = Timing::sInstance.GetDeltaTime();
	mTTL -= dt;
	if (mTTL <= 0)
	{
		SetDoesWantToDie(true);
	}
	else mSpriteComponent->SetTextureRect(mAnimation.Update(dt));
}