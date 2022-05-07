class TextureManager
{
public:
	static void StaticInit();

	static std::unique_ptr<TextureManager>		sInstance;

	TexturePtr	GetTexture(const ETextures& inTextureName);

private:
	TextureManager();

	bool CacheTexture(ETextures inName, const char* inFileName);
	bool CacheTexture(ETextures inTextureName, const char* inFileName, sf::IntRect area);

	unordered_map< ETextures, TexturePtr >	mNameToTextureMap;
};

