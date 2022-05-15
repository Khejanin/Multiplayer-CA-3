#pragma once
class GetPlayerNameState : public State
{
public:
	GetPlayerNameState();
	void Draw() override;
	bool Update(float dt) override;
	bool HandleEvent(const sf::Event& event) override;

private:
	sf::Text mPleasePutNameText;
	sf::Text mInputPreview;
	string mPlayerName;
};

