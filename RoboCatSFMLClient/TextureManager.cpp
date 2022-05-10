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
	CacheTexture(ETextures::kTank, "../Assets/Textures/Tanx2.png", sf::IntRect(34, 12, 10, 10));
	//Background
	CacheTexture(ETextures::kBackground, "../Assets/Textures/Tanx2.png", sf::IntRect(89, 45, 10, 10));
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
	//Tiles
	CacheTexture(ETextures::kTileUpLeft, "../Assets/Textures/Tanx2.png", sf::IntRect(1, 56, 10, 10));
	CacheTexture(ETextures::kTileUpRight, "../Assets/Textures/Tanx2.png", sf::IntRect(12, 56, 10, 10));
	CacheTexture(ETextures::kTileDownLeft, "../Assets/Textures/Tanx2.png", sf::IntRect(1, 67, 10, 10));
	CacheTexture(ETextures::kTileDownRight, "../Assets/Textures/Tanx2.png", sf::IntRect(12, 67, 10, 10));
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