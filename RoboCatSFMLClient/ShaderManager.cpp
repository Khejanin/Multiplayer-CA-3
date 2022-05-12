#include "RoboCatClientPCH.hpp"

std::unique_ptr<ShaderManager> ShaderManager::sInstance;

void ShaderManager::StaticInit()
{
	sInstance.reset(new ShaderManager());
}

ShaderManager::ShaderManager()
{
	CacheShader(EShaders::kShakePass, "../Assets/Shaders/Shake.vert", "../Assets/Shaders/Shake.frag");
	CacheShader(EShaders::kBrightnessPass, "../Assets/Shaders/Fullpass.vert", "../Assets/Shaders/Brightness.frag");
	CacheShader(EShaders::kDownSamplePass, "../Assets/Shaders/Fullpass.vert", "../Assets/Shaders/DownSample.frag");
	CacheShader(EShaders::kGaussianBlurPass, "../Assets/Shaders/Fullpass.vert", "../Assets/Shaders/GuassianBlur.frag");
	CacheShader(EShaders::kAddPass, "../Assets/Shaders/Fullpass.vert", "../Assets/Shaders/Add.frag");
	CacheShader(EShaders::kBlitPass, "../Assets/Shaders/Fullpass.vert", "../Assets/Shaders/Blit.frag");
}

ShaderPtr ShaderManager::GetShader(const EShaders& p_fontName)
{
	return mNameToShaderMap[p_fontName];
}

bool ShaderManager::CacheShader(EShaders inName, const char* inVertFileName, const char* inFragFileName)
{
	ShaderPtr newShader(new sf::Shader());
	if (!newShader->loadFromFile(inVertFileName, inFragFileName))
		return false;

	mNameToShaderMap[inName] = newShader;
	return true;
}
