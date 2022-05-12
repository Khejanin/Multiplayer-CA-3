//Alex Nogueira / D00242564
#pragma once
class PostEffect : sf::NonCopyable
{
public:
	virtual					~PostEffect();
	virtual void			Apply(const sf::RenderTexture& input, sf::RenderTarget& output) = 0;

	static bool				IsSupported();


protected:
	static void				ApplyShader(const sf::Shader& shader, sf::RenderTarget& output);
};

