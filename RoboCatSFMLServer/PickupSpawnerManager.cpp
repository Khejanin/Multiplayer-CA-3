#include "RoboCatServerPCH.hpp"

PickupSpawnerManager* PickupSpawnerManager::sInstance;

void PickupSpawnerManager::StaticInit(float interval, std::vector<Vector3> spawn_positions, float baseChance)
{
	sInstance = new PickupSpawnerManager(interval, spawn_positions, baseChance);
}

PickupSpawnerManager::PickupSpawnerManager(float interval, std::vector<Vector3> spawn_positions, float base_chance)
	: m_interval(interval), m_chance(base_chance), m_cooldown(interval)
{
	srand(time(NULL));
	auto m_spawn_health = [this](int spawnerId, Vector3& pos)
	{
		SpawnPickup(spawnerId, Pickup::Category::kHealthUp, pos);
	};

	auto m_spawn_fire_rate = [this](int spawnerId, Vector3& pos)
	{
		SpawnPickup(spawnerId, Pickup::Category::kFireRate, pos);
	};

	auto m_spawn_damage_up = [this](int spawnerId, Vector3& pos)
	{
		SpawnPickup(spawnerId, Pickup::Category::kProjectileDamage, pos);
	};

	m_spawn_actions.emplace_back(m_spawn_health);
	m_spawn_actions.emplace_back(m_spawn_fire_rate);
	m_spawn_actions.emplace_back(m_spawn_damage_up);

	SetupSpawners(spawn_positions);
}

void PickupSpawnerManager::SetupSpawners(std::vector<Vector3> spawn_positions)
{
	mSpawners = spawn_positions;
	for (int i = 0; i < spawn_positions.size(); i++)
	{
		mSpawnerOccupancy.emplace_back(false);
	}
}

void PickupSpawnerManager::SpawnPickup(int spawnerId, Pickup::Category category, Vector3 position)
{
	auto go = GameObjectRegistry::sInstance->CreateGameObject('PICK');
	PickupServer* pickup = static_cast<PickupServer*>(go.get());
	pickup->SetPosition(position);
	pickup->SetSpawnerId(spawnerId);
	pickup->SetCategory(category);
}

void PickupSpawnerManager::SetNoLongerOccupied(int spawnerId)
{
	mSpawnerOccupancy[spawnerId] = false;
}

void PickupSpawnerManager::Update()
{
	float dt = Timing::sInstance.GetDeltaTime();
	m_cooldown -= dt;
	if (m_cooldown <= 0.f)
	{
		int rand = std::rand();

		if (rand < RAND_MAX * m_chance)
		{
			int spawner_pos = rand % mSpawners.size();
			int action_pos = rand % m_spawn_actions.size();
			auto child = mSpawners[spawner_pos];
			//If not occupied, continue
			if (!mSpawnerOccupancy[spawner_pos])
			{
				m_spawn_actions[action_pos](spawner_pos,child);
				mSpawnerOccupancy[spawner_pos] = true;
			}
		}

		m_cooldown = m_interval;
	}
}
