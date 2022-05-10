#include "RoboCatServerPCH.hpp"

TileServer::TileServer() : Tile()
{
}

void TileServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

void TileServer::Hit()
{
	mHealth--;
	if (mHealth <= 0)
	{
		SetDoesWantToDie(true);
	}
}
