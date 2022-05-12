class Tank : public DynamicGameObject
{
public:
	CLASS_IDENTIFICATION('TANK', GameObject)

	enum ETankReplicationState
	{
		ETRS_Pose = 1 << 0,
		ETRS_Color = 1 << 1,
		ETRS_PlayerId = 1 << 2,
		ETRS_Health = 1 << 3,
		ETRS_Event = 1 << 4,

		ETRS_AllState = ETRS_Pose | ETRS_Color | ETRS_PlayerId | ETRS_Health | ETRS_Event
	};

	enum ETankEventBitMask
	{
		ETEB_Hurt = 1 << 0,
		ETEB_Pickup = 1 << 1,
		ETEB_Shoot = 1 << 2,
		ETEB_Death = 1 << 3,
	};


	static	GameObject* StaticCreate() { return new Tank(); }

	virtual uint32_t GetAllStateMask()	const override { return ETRS_AllState; }

	virtual void Update() override;

	void ProcessInput(float inDeltaTime, const InputState& inInputState);
	void SimulateMovement(float inDeltaTime);

	void		SetPlayerId(uint32_t inPlayerId) { mPlayerId = inPlayerId; }
	uint32_t	GetPlayerId()						const { return mPlayerId; }

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;
	void PostWrite() override { mTankEvent = 0; }

protected:
	Tank();

private:


	void	AdjustVelocityByThrust(float inDeltaTime);

	float				mMaxLinearSpeed;

	uint32_t			mPlayerId;

protected:

	///move down here for padding reasons...

	float				mLastMoveTimestamp;

	bool				mIsThrusting;
	int					mHealth;

	bool				mIsShooting;

	int					mTankEvent;
};

typedef shared_ptr< Tank >	TankPtr;
