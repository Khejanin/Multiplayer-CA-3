//I take care of rendering things!

class HUD
{
public:

	static void StaticInit();
	static std::unique_ptr< HUD >	sInstance;

	void Render();

	void SetPlayerHealth(int inHealth) { mHealth = inHealth; }
	void SetPlayerHealthOffset(Vector3 offset) { mHealthOffset = offset; }
	void SetScoreBoardOffset(Vector3 offset) { mScoreOffset = offset; }
	void SetBandwithOffset(Vector3 offset) { mBandwidthOrigin = offset; }
	void SetRTTOffset(Vector3 offset) { mRoundTripTimeOrigin = offset; }

private:

	HUD();

	void	RenderBandWidth();
	void	RenderRoundTripTime();
	void	RenderScoreBoard();
	void	RenderHealth();
	void	RenderText(const string& inStr, const Vector3& origin, const Vector3& inColor);

	Vector3										mBandwidthOrigin;
	Vector3										mRoundTripTimeOrigin;
	Vector3										mScoreBoardOrigin;
	Vector3										mScoreOffset;
	Vector3										mHealthOffset;
	int											mHealth;
};



