class ProjectileClient : public Projectile
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new ProjectileClient()); }

	virtual void		Read(InputMemoryBitStream& inInputStream) override;

protected:
	ProjectileClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
