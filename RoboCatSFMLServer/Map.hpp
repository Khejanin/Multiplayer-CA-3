#pragma once
class Map
{
public:
	static void LoadMap(std::string path, int tilesX, std::map<int, Vector3>& tank_spawns, std::vector<Vector3>& pickup_spawners, Vector3 world_center, float spawn_offset);

private:
	static void LoadSpawns(std::string path, std::string layer, std::map<int, Vector3>& tank_spawns, Vector3 world_center, float spawn_offset);
	static void LoadLayer(std::string path, std::string layer, int tilesX);
	static void LoadFile(std::string path, std::string layer, std::function<void(int, int, int)> func);
	static void LoadSpawnAtPos(int xPos, int yPos, int elem, std::map<int, Vector3>& tank_spawns, Vector3 world_center, float spawn_offset);
	static void CreateTileAtPos(int xPos, int yPos, int elem, int tilesX);
};
