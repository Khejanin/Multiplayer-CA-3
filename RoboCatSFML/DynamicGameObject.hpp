#pragma once
class DynamicGameObject : public GameObject
{
public:
	CLASS_IDENTIFICATION('DYGO', GameObject)
	void ProcessCollisions();
	DynamicGameObject* GetAsDynamicGameObject() override { return this; }

protected:
	virtual void HitWall() { return; }

private:
	void ProcessCollisionsWithScreenWalls();

private:
	Vector3				mVelocity;

	//bounce fraction when hitting various things
	float				mWallRestitution;
	float				mCatRestitution;
};

