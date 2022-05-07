class FontManager
{
public:
	static void StaticInit();

	static std::unique_ptr<FontManager> sInstance;

	FontPtr GetFont(const EFonts& p_fontName);

private:
	FontManager();

	bool CacheFont(EFonts inName, const char* inFileName);

	unordered_map< EFonts, FontPtr >	mNameToFontMap;
};

