class Pickup : public GameObject
{
public:
	enum Category
	{
		kHealthUp,
		kFireRate
	};

	CLASS_IDENTIFICATION('PICK', GameObject)

	enum EProjectileReplicationState
	{
		EPRS_Pose = 1 << 0,
		EPRS_Type = 1 << 1,

		EPRS_AllState = EPRS_Pose | EPRS_Type
	};

	static	GameObject* StaticCreate() { return new Pickup(); }

	virtual uint32_t	GetAllStateMask()	const override { return EPRS_AllState; }

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;

	virtual bool HandleCollisionWithDynamicGameObject(DynamicGameObject* inDynGo) override;

	virtual void SetCategory(Category category);
	virtual Category GetCategory() const;

protected:
	Pickup();
	Category mCategory;
};

typedef shared_ptr< Tile >	TilePtr;

