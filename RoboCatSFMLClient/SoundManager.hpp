class SoundManager
{
public:
	static void StaticInit();

	static std::unique_ptr<SoundManager>		sInstance;

	void Play(ESounds effect);
	void Play(ESounds effect, sf::Vector2f position);

	void SetListenerPosition(sf::Vector2f position);
	sf::Vector2f GetListenerPosition() const;

	void RemoveStoppedSounds();

private:
	SoundManager();

	bool CacheSound(ESounds inName, const char* inFileName);

	unordered_map< ESounds, SoundPtr >	mNameToTextureMap;
	std::list<sf::Sound> m_sounds;
};

