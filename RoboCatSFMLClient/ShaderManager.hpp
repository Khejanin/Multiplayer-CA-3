class ShaderManager
{
public:
	static void StaticInit();

	static std::unique_ptr<ShaderManager> sInstance;

	ShaderPtr GetShader(const EShaders& p_fontName);

private:
	ShaderManager();

	bool CacheShader(EShaders inName, const char* inVertFileName, const char* inFragFileName);

	unordered_map< EShaders, ShaderPtr >	mNameToShaderMap;
};

