#pragma once
class PickupServer : public Pickup
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new PickupServer()); }
	void HandleDying() override;
	bool HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo) override;

	void Update() override;
	void SetSpawnerId(int spawnerId) { mSpawnerId = spawnerId; }

protected:
	PickupServer();
	float mTimeToDie;
	int mSpawnerId;
};

