
#include "RoboCatServerPCH.hpp"
#include <iostream>



//uncomment this when you begin working on the server

bool Server::StaticInit()
{
	s_instance.reset(new Server());

	return true;
}

Server::Server()
{
	GameObjectRegistry::sInstance->RegisterCreationFunction('TANK', TankServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('PROJ', ProjectileServer::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('TILE', TileServer::StaticCreate);

	InitNetworkManager();

	// Setup latency
	float latency = 0.0f;
	string latencyString = StringUtils::GetCommandLineArg(2);
	if (!latencyString.empty())
	{
		latency = stof(latencyString);
	}
	NetworkManagerServer::sInstance->SetSimulatedLatency(latency);
}


int Server::Run()
{
	SetupWorld();

	return Engine::Run();
}

bool Server::InitNetworkManager()
{
	string portString = StringUtils::GetCommandLineArg(1);
	uint16_t port = stoi(portString);

	return NetworkManagerServer::StaticInit(port);
}


namespace
{

	void CreateRandomMice(int inMouseCount)
	{
		Vector3 mouseMin(100.f, 100.f, 0.f);
		Vector3 mouseMax(1180.f, 620.f, 0.f);
		GameObjectPtr go;

		//make a mouse somewhere- where will these come from?
		for (int i = 0; i < inMouseCount; ++i)
		{
			go = GameObjectRegistry::sInstance->CreateGameObject('MOUS');
			Vector3 mouseLocation = RoboMath::GetRandomVector(mouseMin, mouseMax);
			go->SetPosition(mouseLocation);
		}
	}


}


void Server::SetupWorld()
{
	//We need to load the map
	std::vector<Vector3> spawner_positions;
	Map::LoadMap("../Assets/Arena Data/map", 16, m_tank_spawns, spawner_positions, Vector3(WORLD_WIDTH / 2, WORLD_HEIGHT / 2, 0), 45.f);
	//TODO: SPAWNERS NEXT
}

void Server::DoFrame()
{
	NetworkManagerServer::sInstance->ProcessIncomingPackets();

	NetworkManagerServer::sInstance->CheckForDisconnects();

	NetworkManagerServer::sInstance->RespawnCats();

	Engine::DoFrame();

	NetworkManagerServer::sInstance->SendOutgoingPackets();
}

void Server::HandleNewClient(ClientProxyPtr inClientProxy)
{

	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->AddEntry(playerId, inClientProxy->GetName());
	SpawnTankForPlayer(playerId);
}

void Server::SpawnTankForPlayer(int inPlayerId)
{
	TankPtr tank = std::static_pointer_cast<Tank>(GameObjectRegistry::sInstance->CreateGameObject('TANK'));
	tank->SetColor(ScoreBoardManager::sInstance->GetEntry(inPlayerId)->GetColor());
	tank->SetPlayerId(inPlayerId);
	//gotta pick a better spawn location than this...
	tank->SetPosition(m_tank_spawns[inPlayerId]);
}

void Server::HandleLostClient(ClientProxyPtr inClientProxy)
{
	//kill client's cat
	//remove client from scoreboard
	int playerId = inClientProxy->GetPlayerId();

	ScoreBoardManager::sInstance->RemoveEntry(playerId);
	TankPtr tank = GetTankForPlayer(playerId);
	if (tank)
	{
		tank->SetDoesWantToDie(true);
	}
}

TankPtr Server::GetTankForPlayer(int inPlayerId)
{
	//run through the objects till we find the cat...
	//it would be nice if we kept a pointer to the cat on the clientproxy
	//but then we'd have to clean it up when the cat died, etc.
	//this will work for now until it's a perf issue
	const auto& gameObjects = World::sInstance->GetGameObjects();
	for (int i = 0, c = gameObjects.size(); i < c; ++i)
	{
		GameObjectPtr go = gameObjects[i];
		if(go->GetClassId() == 'TANK')
		{
			Tank* tank = static_cast<Tank*>(go.get());
			if (tank->GetPlayerId() == inPlayerId)
			{
				return std::static_pointer_cast<Tank>(go);
			}
		}
	}

	return nullptr;

}
