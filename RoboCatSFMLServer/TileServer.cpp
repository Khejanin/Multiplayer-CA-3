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

bool TileServer::HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo)
{
	switch (inDynGo->GetClassId())
	{
	case 'PROJ':
		{
			Projectile* proj = dynamic_cast<Projectile*>(inDynGo);

			//projectile dies!
			proj->SetDoesWantToDie(true);

			Hit();
		}
		break;
		return false;
	}

	return true;
}
