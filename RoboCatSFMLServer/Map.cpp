#include "RoboCatServerPCH.hpp"
#include "fstream"

void Map::LoadMap(std::string path, int tilesX, std::map<int, Vector3>& tank_spawns,
	std::vector<Vector3>& pickup_spawners, Vector3 world_center, float spawn_offset)
{
	//Dont need to load border for now
	/*if (load_map)
	{
		LoadLayer(path, "_Border.csv", textureAtlas, tilesX, Category::kWallTile);
		return;
	}*/
	//LoadLayer(path, "_Destroyable.csv", tilesX);
	LoadSpawns(path, "_Spawns.csv", tank_spawns, world_center, spawn_offset);

	LoadFile(path, "_Pickups.csv", [&pickup_spawners](int xPos, int yPos, int elem)
		{
			if (elem == -1) return;
			Vector3 pos(xPos, yPos, 0);
			pickup_spawners.push_back(pos);
		});
}

void Map::CreateTileAtPos(int xPos, int yPos, int elem, int tilesX)
{
	TilePtr tile = std::static_pointer_cast<Tile>(GameObjectRegistry::sInstance->CreateGameObject('TILE'));
	tile->SetPosition(Vector3(xPos, yPos, 0));
	tile->SetTexId(elem);
}

void Map::LoadSpawns(std::string path, std::string layer, std::map<int, Vector3>& tank_spawns,
	Vector3 world_center, float spawn_offset)
{
	LoadFile(path, layer, [&tank_spawns, world_center, spawn_offset](int xPos, int yPos, int elem)
		{
			LoadSpawnAtPos(xPos, yPos, elem, tank_spawns, world_center, spawn_offset);
		});
}

void Map::LoadLayer(std::string path, std::string layer, int tilesX)
{
	LoadFile(path, layer, [tilesX](int xPos, int yPos, int elem)
		{
			CreateTileAtPos(xPos, yPos, elem, tilesX);
		});
}

void Map::LoadFile(std::string path, std::string layer, std::function<void(int, int, int)> func)
{
	std::ifstream file(path + layer);
	std::string line;

	int xPos = 0;
	int yPos = 0;

	while (getline(file, line))
	{
		for (auto value : StringUtils::Split(line, ','))
		{
			int elem = std::stoi(value);
			if (elem != -1)
			{
				func(xPos, yPos, elem);
			}

			xPos += 50;
		}
		xPos = 0;
		yPos += 50;
	}
	file.close();
}

void Map::LoadSpawnAtPos(int xPos, int yPos, int elem, std::map<int, Vector3>& tank_spawns,
	Vector3 world_center, float spawn_offset)
{
	if (elem == -1) return;
	Vector3 pos(xPos, yPos, 0);
	Vector3 offsetDir = world_center - pos;
	offsetDir.Normalize();
	pos = pos + offsetDir * spawn_offset;
	tank_spawns[elem] = pos;
}