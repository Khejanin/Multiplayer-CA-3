#include "RoboCatClientPCH.hpp"

std::unique_ptr< PostEffectsManager >	PostEffectsManager::sInstance;

void PostEffectsManager::StaticInit()
{
	sInstance.reset(new PostEffectsManager());
	sInstance->mCacheRT.create(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void PostEffectsManager::Update()
{
	if (sInstance->mShakeEffectTimer > 0)
	{
		sInstance->mShakeEffectTimer -= Timing::sInstance.GetDeltaTime();
	}
}

void PostEffectsManager::ShakeItBaby()
{
	//sInstance->mShakeEffectTimer = sInstance->mMaxShakeTimer;
}

void PostEffectsManager::ApplyPostEffects()
{
	if (sInstance->mShakeEffectTimer > 0)
	{
		LOG("ShakeShake", 0)
		//Clear CacheRT
		sInstance->mCacheRT.clear(sf::Color::Black);
		//Blit RT to CacheRT
		BlitPass::Apply(*WindowManager::mRenderTexture, sInstance->mCacheRT);
		//Copy back with the Shader to RT
		float intensity = sInstance->mMaxShakeIntensity * sInstance->mShakeEffectTimer / sInstance->mMaxShakeTimer;
		sInstance->mShakeEffect.Apply(sInstance->mCacheRT, *WindowManager::mRenderTexture, Timing::sInstance.GetTimef(), intensity);
	}
}

PostEffectsManager::PostEffectsManager():
	mMaxShakeIntensity(10),
	mMaxShakeTimer(0.25f)
{
}
