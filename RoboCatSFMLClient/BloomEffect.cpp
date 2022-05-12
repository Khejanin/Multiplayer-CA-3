//Alex Nogueira / D00242564
#include "RoboCatClientPCH.hpp"

BloomEffect::BloomEffect()
{
}

void BloomEffect::Apply(const sf::RenderTexture& input, sf::RenderTarget& output)
{
	PrepareTextures(input.getSize());

	FilterBright(input, m_brightness_texture);

	Downsample(m_brightness_texture, m_firstpass_textures[0]);
	BlurMultipass(m_firstpass_textures);

	Downsample(m_firstpass_textures[0], m_secondpass_textures[0]);
	BlurMultipass(m_secondpass_textures);

	Add(m_firstpass_textures[0], m_secondpass_textures[0], m_firstpass_textures[1]);
	m_firstpass_textures[1].display();
	Add(input, m_firstpass_textures[1], output);
}

void BloomEffect::PrepareTextures(sf::Vector2u size)
{
	if (m_brightness_texture.getSize() != size)
	{
		m_brightness_texture.create(size.x, size.y);
		m_brightness_texture.setSmooth(true);

		m_firstpass_textures[0].create(size.x / 2, size.y / 2);
		m_firstpass_textures[0].setSmooth(true);
		m_firstpass_textures[1].create(size.x / 2, size.y / 2);
		m_firstpass_textures[1].setSmooth(true);

		m_secondpass_textures[0].create(size.x / 4, size.y / 4);
		m_secondpass_textures[0].setSmooth(true);
		m_secondpass_textures[1].create(size.x / 4, size.y / 4);
		m_secondpass_textures[1].setSmooth(true);
	}
}

void BloomEffect::FilterBright(const sf::RenderTexture& input, sf::RenderTexture& output)
{
	sf::Shader& brightness = *ShaderManager::sInstance->GetShader(EShaders::kBrightnessPass);

	brightness.setUniform("source", input.getTexture());
	ApplyShader(brightness, output);
	output.display();
}

void BloomEffect::BlurMultipass(RenderTextureArray& renderTextures)
{
	sf::Vector2u textureSize = renderTextures[0].getSize();

	for (std::size_t count = 0; count < 2; ++count)
	{
		Blur(renderTextures[0], renderTextures[1], sf::Vector2f(0.f, 1.f / textureSize.y));
		Blur(renderTextures[1], renderTextures[0], sf::Vector2f(1.f / textureSize.x, 0.f));
	}
}

void BloomEffect::Blur(const sf::RenderTexture& input, sf::RenderTexture& output, sf::Vector2f offsetFactor)
{
	sf::Shader& gaussianBlur = *ShaderManager::sInstance->GetShader(EShaders::kGaussianBlurPass);

	gaussianBlur.setUniform("source", input.getTexture());
	gaussianBlur.setUniform("offsetFactor", offsetFactor);
	ApplyShader(gaussianBlur, output);
	output.display();
}

void BloomEffect::Downsample(const sf::RenderTexture& input, sf::RenderTexture& output)
{
	sf::Shader& downSampler = *ShaderManager::sInstance->GetShader(EShaders::kDownSamplePass);

	downSampler.setUniform("source", input.getTexture());
	downSampler.setUniform("sourceSize", sf::Vector2f(input.getSize()));
	ApplyShader(downSampler, output);
	output.display();
}

void BloomEffect::Add(const sf::RenderTexture& source, const sf::RenderTexture& bloom, sf::RenderTarget& output)
{
	sf::Shader& adder = *ShaderManager::sInstance->GetShader(EShaders::kAddPass);

	adder.setUniform("source", source.getTexture());
	adder.setUniform("bloom", bloom.getTexture());
	ApplyShader(adder, output);
}