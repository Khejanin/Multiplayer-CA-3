class TileClient : public Tile
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new TileClient()); }
	virtual void		Read(InputMemoryBitStream& inInputStream) override;
	void SetTexId(int texId) override;

protected:
	TileClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};