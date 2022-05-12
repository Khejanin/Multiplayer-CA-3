#include "RoboCatClientPCH.hpp"

void BlitPass::Apply(const sf::RenderTexture& input, sf::RenderTarget& output)
{
	sf::Shader& shader = *ShaderManager::sInstance->GetShader(EShaders::kBlitPass);
	shader.setUniform("source", input.getTexture());
	ApplyShader(shader, output);
}
