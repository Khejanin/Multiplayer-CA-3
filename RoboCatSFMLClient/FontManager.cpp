#include "RoboCatClientPCH.hpp"

std::unique_ptr<FontManager> FontManager::sInstance;

void FontManager::StaticInit()
{
	sInstance.reset(new FontManager());
}

FontManager::FontManager()
{
	CacheFont(EFonts::kMain, "../Assets/Fonts/Sansation.ttf");
}

FontPtr FontManager::GetFont(const EFonts& p_fontName)
{
	return mNameToFontMap[p_fontName];
}

bool FontManager::CacheFont(EFonts inName, const char* inFileName)
{
	FontPtr newFont(new sf::Font());
	if (!newFont->loadFromFile(inFileName))
		return false;

	mNameToFontMap[inName] = newFont;
	return true;
}