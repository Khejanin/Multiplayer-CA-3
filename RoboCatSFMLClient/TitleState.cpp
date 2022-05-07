//Alex Nogueira / D00242564
#include "RoboCatClientPCH.hpp"

TitleState::TitleState()
: State()
, m_show_text(true)
, m_text_effect_time(0)
{
	m_background_sprite.setTexture(*TextureManager::sInstance->GetTexture(ETextures::kTitleScreen));
	m_text.setFont(*FontManager::sInstance->GetFont(EFonts::kMain));
	m_text.setString("Press any key to continue");
	Utility::CentreOrigin(m_text);
	WindowManager::SetDefaultView();
	m_text.setPosition(WindowManager::sInstance->getView().getSize() / 2.f);
}

void TitleState::Draw()
{
	sf::RenderWindow& window = *WindowManager::sInstance;
	WindowManager::SetDefaultView();
	window.draw(m_background_sprite);

	if(m_show_text)
	{
		window.draw(m_text);
	}
}

bool TitleState::Update(float dt)
{
	m_text_effect_time += dt;

	if(m_text_effect_time >= 0.5)
	{
		m_show_text = !m_show_text;
		m_text_effect_time = 0;
	}
	return true;
}

bool TitleState::HandleEvent(const sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		RequestStackPop();
		RequestStackPush(EState::kMenu);
	}
	return false;
}
