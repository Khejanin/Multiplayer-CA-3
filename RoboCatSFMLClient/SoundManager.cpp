#include "RoboCatClientPCH.hpp"

std::unique_ptr< SoundManager >		SoundManager::sInstance;

namespace
{
	// Sound coordinate system, point of view of a player in front of the screen:
	// X = left; Y = up; Z = back (out of the screen)
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 400.f;
	const float MinDistance3D = std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
}

void SoundManager::StaticInit()
{
	sInstance.reset(new SoundManager());
}

SoundManager::SoundManager()
{
	CacheSound(ESounds::kFire, "../Assets/Sounds/Gunfire.wav");
	CacheSound(ESounds::kPlayer1FireMissile, "../Assets/Sounds/Gunfire5.wav");
	CacheSound(ESounds::kPlayer2FireMissile, "../Assets/Sounds/Gunfire5.wav");
	CacheSound(ESounds::kTankDeath, "../Assets/Sounds/TankExplosion.wav");
	CacheSound(ESounds::kTankExplosion2, "../Assets/Sounds/TankExplosion.wav");
	CacheSound(ESounds::kMissileExplosion1, "../Assets/Sounds/MissileExplosion.wav");
	CacheSound(ESounds::kMissileExplosion2, "../Assets/Sounds/MissileExplosion.wav");
	CacheSound(ESounds::kHit, "../Assets/Sounds/Hit.wav");
	CacheSound(ESounds::kPlayer2Hit, "../Assets/Sounds/Hit.wav");
	CacheSound(ESounds::kCollectPickup, "../Assets/Sounds/CollectPickup.wav");
	CacheSound(ESounds::kRepair, "../Assets/Sounds/Repair.wav");
	CacheSound(ESounds::kRestock, "../Assets/Sounds/Restock.wav");
	CacheSound(ESounds::kMissileUpgrade, "../Assets/Sounds/Missile.wav");
	CacheSound(ESounds::kFireRateUpgrade, "../Assets/Sounds/FireRate.wav");
	CacheSound(ESounds::kHealthFull, "../Assets/Sounds/HealthFull.wav");
	CacheSound(ESounds::kButton, "../Assets/Sounds/Button.wav");
}

bool SoundManager::CacheSound(ESounds inName, const char* inFileName)
{
	SoundPtr newSound(new sf::SoundBuffer());

	if (!newSound->loadFromFile(inFileName))
	{
		return false;
	}

	mNameToTextureMap[inName] = newSound;

	return true;
}


void SoundManager::Play(ESounds effect)
{
	Play(effect, GetListenerPosition());
}

void SoundManager::Play(ESounds effect, Vector3 position)
{
	m_sounds.emplace_back(sf::Sound());
	sf::Sound& sound = m_sounds.back();

	sound.setBuffer(*(mNameToTextureMap[effect].get()));
	sound.setPosition(position.mX, -position.mY, 0.f);
	sound.setAttenuation(Attenuation);
	sound.setMinDistance(MinDistance3D);

	sound.play();
}

void SoundManager::RemoveStoppedSounds()
{
	m_sounds.remove_if([](const sf::Sound& s)
		{
			return s.getStatus() == sf::Sound::Stopped;
		});
}

void SoundManager::SetListenerPosition(Vector3 position)
{
	sf::Listener::setPosition(position.mX, -position.mY, ListenerZ);
}

Vector3 SoundManager::GetListenerPosition() const
{
	sf::Vector3f position = sf::Listener::getPosition();
	return Vector3(position.x, -position.y, 0);
}

