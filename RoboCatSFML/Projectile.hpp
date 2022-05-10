class Projectile : public DynamicGameObject
{
public:

	CLASS_IDENTIFICATION('PROJ', GameObject)

	enum EProjectileReplicationState
	{
		EPRS_Pose = 1 << 0,
		EPRS_Color = 1 << 1,
		EPRS_PlayerId = 1 << 2,

		EPRS_AllState = EPRS_Pose | EPRS_Color | EPRS_PlayerId
	};

	static	GameObject* StaticCreate() { return new Projectile(); }

	virtual uint32_t	GetAllStateMask()	const override { return EPRS_AllState; }

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

	void		SetPlayerId(int inPlayerId) { mPlayerId = inPlayerId; }
	int			GetPlayerId() const { return mPlayerId; }

	void		InitFromShooter(Tank* inShooter);

	virtual void Update() override;

	virtual bool HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo) override;

protected:
	Projectile();
	float		mMuzzleSpeed;
	int			mPlayerId;
	//bool		mIsMissile;

};

typedef shared_ptr< Projectile >	ProjectilePtr;