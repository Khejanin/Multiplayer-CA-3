class SoundManager
{
public:
	static void StaticInit();

	static std::unique_ptr<SoundManager>		sInstance;

	void Play(ESounds effect);
	void Play(ESounds effect, Vector3 position);

	void SetListenerPosition(Vector3 position);
	Vector3 GetListenerPosition() const;

	void RemoveStoppedSounds();

private:
	SoundManager();

	bool CacheSound(ESounds inName, const char* inFileName);

	unordered_map< ESounds, SoundPtr >	mNameToTextureMap;
	list<sf::Sound> m_sounds;
};

