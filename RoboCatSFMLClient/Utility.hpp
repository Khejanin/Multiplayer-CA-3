#pragma once

namespace sf
{
	class Sprite;
	class Text;
}

class Utility
{
public:
	static void CentreOrigin(sf::Sprite& sprite);
	static void CentreOrigin(sf::Text& text);
	static void CentreOrigin(Animation& animation);
	static std::string toString(sf::Keyboard::Key key);
	static sf::Vector2f UnitVector(sf::Vector2f vector);
	static float Length(sf::Vector2f vector);
	static int RandomInt(int exclusive_max);
};

