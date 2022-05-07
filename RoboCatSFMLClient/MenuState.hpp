class MenuState : public State
{
public:
	MenuState();
	virtual void Draw();
	virtual bool Update(float dt);
	virtual bool HandleEvent(const sf::Event& event);

private:
	sf::Sprite m_background_sprite;
	GUI::Container m_gui_container;
};

