class Tile : public GameObject
{
public:

	CLASS_IDENTIFICATION('TILE', GameObject)

	enum EProjectileReplicationState
	{
		ETRS_Pose = 1 << 0,
		ETRS_Tex = 1 << 1,

		ETRS_AllState = ETRS_Pose | ETRS_Tex
	};

	static	GameObject* StaticCreate() { return new Tile(); }

	virtual uint32_t	GetAllStateMask()	const override { return ETRS_AllState; }

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

	virtual bool HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo) override;

	virtual void SetTexId(int texId);
	virtual int GetTexId() const;

protected:
	Tile();
	int mHealth;
	int mTexId;
};

typedef shared_ptr< Tile >	TilePtr;