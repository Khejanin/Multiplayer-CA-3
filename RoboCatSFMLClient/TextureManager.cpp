#include "RoboCatClientPCH.hpp"

std::unique_ptr< TextureManager >		TextureManager::sInstance;

void TextureManager::StaticInit()
{
	sInstance.reset(new TextureManager());
}

TextureManager::TextureManager()
{
	//MENU
	
	//Background
	CacheTexture(ETextures::kTitleScreen, "../Assets/Textures/TitleScreen.png");
	//Buttons
	CacheTexture(ETextures::kButtonNormal, "../Assets/Textures/ButtonNormal.png");
	CacheTexture(ETextures::kButtonSelected, "../Assets/Textures/ButtonSelected.png");
	CacheTexture(ETextures::kButtonPressed, "../Assets/Textures/ButtonPressed.png");

	//GAME
	
	//Tanks
	CacheTexture(ETextures::kTank, "../Assets/Textures/Tanx2.png", sf::IntRect(1, 12, 10, 10));
	//Background
	CacheTexture(ETextures::kBackground, "../Assets/Textures/Tanx2.png", sf::IntRect(88, 44, 10, 10));
	//Pickups
	CacheTexture(ETextures::kHealthRefill, "../Assets/Textures/HealthRefill.png");
	CacheTexture(ETextures::kAmmoRefill, "../Assets/Textures/FireSpread.png");
	CacheTexture(ETextures::kExplosiveShots, "../Assets/Textures/MissileRefill.png");
	CacheTexture(ETextures::kFireRate, "../Assets/Textures/FireRate.png");
	//Projectiles
	CacheTexture(ETextures::kBullet, "../Assets/Textures/Bullet2.png");
	CacheTexture(ETextures::kMissile, "../Assets/Textures/Missile.png");
	//FX
	CacheTexture(ETextures::kExplosion, "../Assets/Textures/Explosion.png");
}

TexturePtr	TextureManager::GetTexture(const ETextures& inTextureName)
{
	return mNameToTextureMap[inTextureName];
}

bool TextureManager::CacheTexture(ETextures inTextureName, const char* inFileName, sf::IntRect area)
{
	TexturePtr newTexture(new sf::Texture());

	if (!newTexture->loadFromFile(inFileName, area))
	{
		return false;
	}

	mNameToTextureMap[inTextureName] = newTexture;

	return true;
}

bool TextureManager::CacheTexture(ETextures inTextureName, const char* inFileName)
{
	TexturePtr newTexture(new sf::Texture());

	if (!newTexture->loadFromFile(inFileName))
	{
		return false;
	}

	mNameToTextureMap[inTextureName] = newTexture;

	return true;
}