#include "RoboCatServerPCH.hpp"


PickupServer::PickupServer()
{
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 10.f;
}

void PickupServer::HandleDying()
{
	PickupSpawnerManager::sInstance->SetNoLongerOccupied(mSpawnerId);
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

bool PickupServer::HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo)
{
	if(inDynGo->GetClassId() == 'TANK')
	{
		TankServer* tank = dynamic_cast<TankServer*>(inDynGo);
		switch(mCategory)
		{
		case kHealthUp:
			tank->Heal(25);
			break;
		case kFireRate:
			tank->ApplyFireRateUpgrade();
			break;
		}
		tank->UpgradeApplied();
		SetDoesWantToDie(true);
	}
	return false;
}

void PickupServer::Update()
{
	Pickup::Update();

	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
	{
		SetDoesWantToDie(true);
	}
}
