#include "RoboCatClientPCH.hpp"

MenuState::MenuState()
: State()
{
	sf::Texture& texture = *TextureManager::sInstance->GetTexture(ETextures::kTitleScreen);

	m_background_sprite.setTexture(texture);

	auto play_button = std::make_shared<GUI::Button>();
	play_button->setPosition(100, 300);
	play_button->SetText("Play");
	play_button->SetCallback([this]()
	{
		RequestStackPop();
		RequestStackPush(EState::kGame);
	});

	auto host_play_button = std::make_shared<GUI::Button>();
	host_play_button->setPosition(100, 350);
	host_play_button->SetText("Host");
	host_play_button->SetCallback([this]()
	{
		RequestStackPop();
		RequestStackPush(EState::kHostGame);
	});

	auto join_play_button = std::make_shared<GUI::Button>();
	join_play_button->setPosition(100, 400);
	join_play_button->SetText("Join");
	join_play_button->SetCallback([this]()
	{
		RequestStackPop();
		RequestStackPush(EState::kJoinGame);
	});

	auto settings_button = std::make_shared<GUI::Button>();
	settings_button->setPosition(100, 450);
	settings_button->SetText("Settings");
	settings_button->SetCallback([this]()
	{
		RequestStackPush(EState::kSettings);
	});

	auto exit_button = std::make_shared<GUI::Button>();
	exit_button->setPosition(100, 500);
	exit_button->SetText("Exit");
	exit_button->SetCallback([this]()
	{
		RequestStackPop();
	});

	m_gui_container.Pack(play_button);
	m_gui_container.Pack(host_play_button);
	m_gui_container.Pack(join_play_button);
	m_gui_container.Pack(settings_button);
	m_gui_container.Pack(exit_button);

	// Play menu theme
	//context.music->Play(MusicThemes::kMenuTheme);
}

void MenuState::Draw()
{
	sf::RenderWindow& window = *WindowManager::sInstance;
	WindowManager::SetDefaultView();
	window.draw(m_background_sprite);
	window.draw(m_gui_container);
	
}

bool MenuState::Update(float dt)
{
	return true;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
	m_gui_container.HandleEvent(event);
	return false;
}

