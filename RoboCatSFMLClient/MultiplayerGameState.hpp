#pragma once
class MultiplayerGameState : public State
{
public:
	MultiplayerGameState();
	virtual void Draw();
	virtual bool Update(float dt);
	virtual bool HandleEvent(const sf::Event& event);
};

