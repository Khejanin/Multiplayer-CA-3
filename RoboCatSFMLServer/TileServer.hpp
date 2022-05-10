class TileServer : public Tile
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new TileServer()); }
	void HandleDying() override;

	void Hit();
	bool HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo) override;

protected:
	TileServer();
};

