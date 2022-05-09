class MouseServer : public Mouse
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new MouseServer()); }
	void HandleDying() override;
	virtual bool HandleCollisionWithDynamicGameObject(DynamicGameObject* inCat) override;

protected:
	MouseServer();
};

