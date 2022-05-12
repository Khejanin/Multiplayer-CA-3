//Alex Nogueira / D00242564
#pragma once
class BlitPass : public PostEffect
{
public:
	static void Apply(const sf::RenderTexture& input, sf::RenderTarget& output);
};

