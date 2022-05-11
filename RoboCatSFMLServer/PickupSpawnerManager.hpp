#pragma once
class PickupSpawnerManager
{
public:
	static PickupSpawnerManager* sInstance;
	static void				StaticInit(float interval, std::vector<Vector3> spawn_positions, float baseChance);
	void Update();
	void SetNoLongerOccupied(int spawnerId);
private:
	PickupSpawnerManager(float interval, std::vector<Vector3> spawn_positions, float baseChance);
	void SetupSpawners(std::vector<Vector3> spawn_positions);
	void SpawnPickup(int spawnerId, Pickup::Category category, Vector3 position);

private:
	std::vector<std::function<void(int, Vector3&)>> m_spawn_actions;
	std::vector<Vector3> mSpawners;
	std::vector<bool> mSpawnerOccupancy;
	float m_cooldown;
	float m_interval;
	float m_chance;
};

