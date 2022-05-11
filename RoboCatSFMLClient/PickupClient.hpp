#pragma once
class PickupClient : public Pickup
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new PickupClient()); }
	virtual void		Read(InputMemoryBitStream& inInputStream) override;
	void SetCategory(Category category) override;

protected:
	PickupClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};