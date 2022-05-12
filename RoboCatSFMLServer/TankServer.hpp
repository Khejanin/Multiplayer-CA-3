#pragma once
class TankServer : public Tank
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new TankServer()); }
	virtual void HandleDying() override;

	virtual void Update() override;

	void SetCatControlType(ECatControlType inCatControlType) { mCatControlType = inCatControlType; }

	void UpgradeApplied();
	void ApplyFireRateUpgrade();
	void ApplyDamageUpgrade();
	void TakeDamage(int inDamagingPlayerId, int damageAmount);
	void Heal(int healAmount);

protected:
	TankServer();

private:
	void HandleShooting();

	ECatControlType	mCatControlType;


	float		mTimeOfNextShot;
	float		mTimeBetweenShots;
	float		mFireRateTimer;
	float		mDamageTimer;
};