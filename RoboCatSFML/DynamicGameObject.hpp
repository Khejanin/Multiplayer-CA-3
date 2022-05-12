#pragma once
class DynamicGameObject : public GameObject
{
public:
	CLASS_IDENTIFICATION('DYGO', GameObject)
	void ProcessCollisions();
	DynamicGameObject* GetAsDynamicGameObject() override { return this; }

	virtual void			SetVelocity(const Vector3& inVelocity) { mVelocity = inVelocity; }
	virtual const Vector3&   GetVelocity()					 const { return mVelocity; }

protected:
	DynamicGameObject();
	virtual void HitWall() { return; }

private:
	void ProcessCollisionsWithWorldBounds();

protected:
	Vector3				mVelocity;
	bool				mCollidesWithWorldBounds;

private:
	//bounce fraction when hitting various things
	float				mWallRestitution;
	float				mDynGoRestitution;
};

