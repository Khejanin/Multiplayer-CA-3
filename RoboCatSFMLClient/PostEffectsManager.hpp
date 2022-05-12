#pragma once
class PostEffectsManager
{
public:
	static void StaticInit();
	static std::unique_ptr< PostEffectsManager >	sInstance;

	static void Update();
	static void ShakeItBaby();
	static void ApplyPostEffects();

private:
	PostEffectsManager();
	ShakeEffect mShakeEffect;
	float mShakeEffectTimer;
	sf::RenderTexture mCacheRT;
	float mMaxShakeIntensity;
	float mMaxShakeTimer;
};
