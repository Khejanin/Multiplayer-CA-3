//Alex Nogueira / D00242564 
#include "RoboCatClientPCH.hpp"

ShakeEffect::ShakeEffect()
{
}

void ShakeEffect::Apply(const sf::RenderTexture& input, sf::RenderTarget& output)
{
	Apply(input, output, 1, 1);
}

void ShakeEffect::Apply(const sf::RenderTexture& input, sf::RenderTarget& output, float time, float intensity)
{
	sf::Shader& shake = *ShaderManager::sInstance->GetShader(EShaders::kShakePass);
	
	shake.setUniform("time", time / 1000.f);
	shake.setUniform("intensity", intensity);

	shake.setUniform("source", input.getTexture());
	
	shake.setUniformArray("offsets", vectorArray, 9);

	float blur_kernel[9] = {
		1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
		2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
		1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
	};

	shake.setUniformArray("blur_kernel", blur_kernel, 9);

	ApplyShader(shake, output);
}


