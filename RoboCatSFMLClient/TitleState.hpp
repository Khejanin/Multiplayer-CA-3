//Alex Nogueira / D00242564
class TitleState : public State
{
public:
	TitleState();
	void Draw() override;
	bool Update(float dt) override;
	bool HandleEvent(const sf::Event& event) override;

private:
	sf::Sprite m_background_sprite;
	sf::Text m_text;

	bool m_show_text;
	float m_text_effect_time;
};

