#define CLASS_IDENTIFICATION(in_code, in_class) \
enum {kClassId = in_code}; \
virtual uint32_t GetClassId() const {return kClassId;} \
static GameObject* CreateInstance() { return static_cast<GameObject*>(new in_class());}\

class GameObject
{
public:
	CLASS_IDENTIFICATION('GOBJ', GameObject)

	GameObject();
	virtual ~GameObject() {}

	virtual DynamicGameObject* GetAsDynamicGameObject() { return nullptr; }

	virtual uint32_t GetAllStateMask() const { return 0; }

	//return whether to keep processing collision
	virtual bool HandleCollisionWithDynamicGameObject(DynamicGameObject* dynGo) { (void)dynGo; return true; }

	virtual void Update();

	virtual void HandleDying() {}

	void SetIndexInWorld(int inIndex) { mIndexInWorld = inIndex; }
	int	GetIndexInWorld()				const { return mIndexInWorld; }

	void SetRotation(float inRotation);
	float GetRotation()					const { return mRotation; }

	void SetScale(float inScale) { mScale = inScale; }
	float GetScale()						const { return mScale; }

	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& inPosition) { mPosition = inPosition; }

	sf::FloatRect GetBounds();
	void SetCanCollide(bool canCollide) { mCanCollide = canCollide; }
	bool GetCanCollide() const { return mCanCollide; }

	const Vector3& GetSize() const { return mSize; }
	void SetSize(const Vector3& inSize) { mSize = inSize; }

	Vector3	GetForwardVector() const;

	void SetColor(const Vector3& inColor) { mColor = inColor; }
	const Vector3& GetColor() const { return mColor; }
	
	void SetPriority(const int priority) { mPriority = priority; }
	const int GetPriority() const { return mPriority; }

	bool DoesWantToDie() const { return mDoesWantToDie; }
	void SetDoesWantToDie(bool inWants) { mDoesWantToDie = inWants; }

	int	GetNetworkId() const { return mNetworkId; }
	void SetNetworkId(int inNetworkId);

	virtual void PostWrite() {}
	virtual uint32_t Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const { (void)inOutputStream; (void)inDirtyState; return 0; }
	virtual void Read(InputMemoryBitStream& inInputStream) { (void)inInputStream; }

private:
	Vector3	mPosition;
	Vector3 mSize;
	Vector3	mColor;
	int mPriority;
	bool mCanCollide = false;

	float mRotation;
	float mScale;
	int	mIndexInWorld;

	bool mDoesWantToDie;

	int	mNetworkId;

};

typedef shared_ptr< GameObject > GameObjectPtr;
