#include "RoboCatServerPCH.hpp"

ProjectileServer::ProjectileServer()
{
	//projectile lives five seconds...
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 3.0f;
}

void ProjectileServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

void ProjectileServer::Update()
{
	float deltaTime = Timing::sInstance.GetDeltaTime();

	SetPosition(GetPosition() + mVelocity * deltaTime);

	NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), EPRS_Pose);

	ProcessCollisions();

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

				dynamic_cast<TankServer*>(tank)->TakeDamage(GetPlayerId(), mDoubleDamage ? 20 : 10);
			}
		}
		break;
	}

	return false;
}
