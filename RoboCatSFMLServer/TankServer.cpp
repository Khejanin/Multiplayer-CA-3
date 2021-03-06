#include "RoboCatServerPCH.hpp"

TankServer::TankServer() :
	mCatControlType(ESCT_Human),
	mTimeOfNextShot(0.f),
	mTimeBetweenShots(0.5f),
	mFireRateTimer(0.f),
	mGameTimer(120.f),
	mGameClosed(false)
{}


void TankServer::HandleDying()
{
	mTankEvent |= ETEB_Death;
	NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ETRS_Event);
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

void TankServer::Update()
{
	Tank::Update();

	float dt = Timing::sInstance.GetDeltaTime();

	//Tick down the upgrade timer
	if (mFireRateTimer > 0) 
	{
		mFireRateTimer -= dt;
		if (mFireRateTimer <= 0)
		{
			mTimeBetweenShots = 0.5f;
		}
	}

	if (mDamageTimer > 0)
	{
		mDamageTimer-= dt;
	}
	

	if (mGameTimer > 0)
	{
		mGameTimer -= dt;
		LOG("%f", mGameTimer);
	}
	else
	{
		if (!mGameClosed) {
			NetworkManagerServer::sInstance->SendEndgamePacket(GetPlayerId());
			mGameClosed = true;

		}
		
		
	}

	Vector3 oldLocation = GetPosition();
	Vector3 oldVelocity = GetVelocity();
	float oldRotation = GetRotation();
	
	if (mCatControlType == ESCT_Human)
	{
		//is there a move we haven't processed yet?
		ClientProxyPtr client = NetworkManagerServer::sInstance->GetClientProxy(GetPlayerId());
		if (client)
		{
			MoveList& moveList = client->GetUnprocessedMoveList();
			for (const Move& unprocessedMove : moveList)
			{
				const InputState& currentState = unprocessedMove.GetInputState();

				float deltaTime = unprocessedMove.GetDeltaTime();

				auto x = currentState.GetDesiredHorizontalDelta();

				ProcessInput(deltaTime, currentState);
				SimulateMovement(deltaTime);

				//LOG( "Server Move Time: %3.4f deltaTime: %3.4f left rot at %3.4f", unprocessedMove.GetTimestamp(), deltaTime, GetRotation() );
			}

			moveList.Clear();
		}
	}
	else
	{
		//do some AI stuff
		SimulateMovement(Timing::sInstance.GetDeltaTime());
	}

	HandleShooting();

	if (!RoboMath::Is2DVectorEqual(oldLocation, GetPosition()) ||
		!RoboMath::Is2DVectorEqual(oldVelocity, GetVelocity()) ||
		oldRotation != GetRotation())
	{
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ETRS_Pose);
	}
}

void TankServer::HandleShooting()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if (mIsShooting && time > mTimeOfNextShot)
	{
		mTankEvent |= ETEB_Shoot;
		NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ETRS_Event);
		//not exact, but okay
		mTimeOfNextShot = time + mTimeBetweenShots;

		//fire!
		ProjectilePtr projectile= std::static_pointer_cast<Projectile>(GameObjectRegistry::sInstance->CreateGameObject('PROJ'));
		projectile->InitFromShooter(this, mDamageTimer > 0);
	}
}

void TankServer::UpgradeApplied()
{
	mTankEvent |= ETEB_Pickup;
	NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ETRS_Event);
}

void TankServer::ApplyFireRateUpgrade()
{
	mFireRateTimer = 10.f;
	mTimeBetweenShots = 0.25f;
}

void TankServer::ApplyDamageUpgrade()
{
	mDamageTimer = 10.f;
}

void TankServer::TakeDamage(int inDamagingPlayerId, int damageAmount)
{
	mTankEvent |= ETEB_Hurt;
	NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ETRS_Event);
	mHealth -= damageAmount;
	if (mHealth <= 0.f)
	{
		//score one for damaging player...
		ScoreBoardManager::sInstance->IncScore(inDamagingPlayerId, 100);

		//and you want to die
		SetDoesWantToDie(true);

		//tell the client proxy to make you a new cat
		ClientProxyPtr clientProxy = NetworkManagerServer::sInstance->GetClientProxy(GetPlayerId());
		if (clientProxy)
		{
			clientProxy->HandlePlayerDied();
		}
	}

	//tell the world our health dropped
	NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ETRS_Health);
}

void TankServer::Heal(int healAmount)
{
	mHealth += healAmount;
	if (mHealth > 200) mHealth = 200;
	NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ETRS_Health);
}
