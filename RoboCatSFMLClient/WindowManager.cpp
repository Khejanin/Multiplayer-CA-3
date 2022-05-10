#include "RoboCatClientPCH.hpp"

std::unique_ptr<sf::RenderWindow>	WindowManager::sInstance;
sf::View WindowManager::mCamera;

bool WindowManager::StaticInit()
{
	sInstance.reset(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tanx!", sf::Style::Close));
	sInstance->setKeyRepeatEnabled(false);
	return true;
}

void WindowManager::SetDefaultView()
{
	sInstance->setView(sInstance->getDefaultView());
}

void WindowManager::SetCameraView()
{
	sInstance->setView(mCamera);
}

void WindowManager::SetViewCenter(Vector3 center)
{
	mCamera.setCenter(center.mX, center.mY);
}


