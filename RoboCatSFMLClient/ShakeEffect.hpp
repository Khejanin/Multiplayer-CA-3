//Alex Nogueira / D00242564
#pragma once
class ShakeEffect : public PostEffect
{
public:
	ShakeEffect();

	virtual void Apply(const sf::RenderTexture& input, sf::RenderTarget& output);
	void Apply(const sf::RenderTexture& input, sf::RenderTarget& output, float time, float intensity);


private:
	typedef std::array<sf::RenderTexture, 2> RenderTextureArray;


private:
	float m_counter = 0;
	float m_offset = 1.0f / 300.0f;
	sf::Glsl::Vec2 vectorArray[9] = {
	{ -m_offset,  m_offset  },  // top-left
	{  0.0f,    m_offset  },  // top-center
	{  m_offset,  m_offset  },  // top-right
	{ -m_offset,  0.0f    },  // center-left
	{  0.0f,    0.0f    },  // center-center
	{  m_offset,  0.0f    },  // center - right
	{ -m_offset, -m_offset  },  // bottom-left
	{  0.0f,   -m_offset  },  // bottom-center
	{  m_offset, -m_offset  }   // bottom-right    
	};
};

