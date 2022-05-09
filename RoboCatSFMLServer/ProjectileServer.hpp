class ProjectileServer : public Projectile
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new ProjectileServer()); }
	void HandleDying() override;

	virtual bool		HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo) override;

	virtual void Update() override;

protected:
	ProjectileServer();

private:
	float mTimeToDie;

};
