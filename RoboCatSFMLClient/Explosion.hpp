#pragma once
class Explosion;
typedef shared_ptr< Explosion>	ExplosionPtr;
class Explosion : public GameObject
{
public:
	CLASS_IDENTIFICATION('EXPL', GameObject)
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new Explosion()); }
	void Update() override;

protected:
	Explosion();

private:
	float mTTL;
	SpriteComponentPtr	mSpriteComponent;
	Animation mAnimation;
};

