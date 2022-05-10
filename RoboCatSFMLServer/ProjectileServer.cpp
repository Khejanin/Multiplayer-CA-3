#include "RoboCatServerPCH.hpp"

ProjectileServer::ProjectileServer()
{
	//projectile lives five seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 5.f;
}

void ProjectileServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

void ProjectileServer::Update()
{
	Projectile::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
}

bool ProjectileServer::HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo)
{
	switch (inDynGo->GetClassId())
	{
	case 'TANK':
		{
			Tank* tank = dynamic_cast<Tank*>(inDynGo);
			if (tank->GetPlayerId() != GetPlayerId())
			{
				//kill yourself!
				SetDoesWantToDie(true);

				dynamic_cast<TankServer*>(tank)->TakeDamage(GetPlayerId(), 10);
			}
		}
		break;
	}

	return false;
}
