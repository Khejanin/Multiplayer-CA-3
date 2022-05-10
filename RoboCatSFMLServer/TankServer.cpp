#include "RoboCatServerPCH.hpp"

TankServer::TankServer() :
	mCatControlType(ESCT_Human),
	mTimeOfNextShot(0.f),
	mTimeBetweenShots(0.2f)
{}


void TankServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

void TankServer::Update()
{
	Tank::Update();

	Vector3 oldLocation = GetPosition();
	Vector3 oldVelocity = GetVelocity();
	float oldRotation = GetRotation();
	
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
		//not exact, but okay
		mTimeOfNextShot = time + mTimeBetweenShots;

		//fire!
		ProjectilePtr projectile= std::static_pointer_cast<Projectile>(GameObjectRegistry::sInstance->CreateGameObject('PROJ'));
		projectile->InitFromShooter(this);
	}
}

void TankServer::TakeDamage(int inDamagingPlayerId, int damageAmount)
{
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
