#include "RoboCatClientPCH.hpp"

std::unique_ptr<sf::RenderWindow>	WindowManager::sInstance;

bool WindowManager::StaticInit()
{
	sInstance.reset(new sf::RenderWindow(sf::VideoMode(WORLD_WIDTH, WORLD_HEIGHT), "Tanx!", sf::Style::Close));
	sInstance->setKeyRepeatEnabled(false);
	return true;
}

void WindowManager::SetDefaultView()
{
	sInstance->setView(sInstance->getDefaultView());
}


