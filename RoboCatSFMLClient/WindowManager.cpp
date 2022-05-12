#include "RoboCatClientPCH.hpp"

std::unique_ptr<sf::RenderTexture>	WindowManager::mRenderTexture;
std::unique_ptr<sf::RenderWindow>	WindowManager::mRenderWindow;
sf::View WindowManager::mCamera;

bool WindowManager::StaticInit()
{
	mRenderTexture.reset(new sf::RenderTexture());
	mRenderTexture->create(WINDOW_WIDTH, WINDOW_HEIGHT);
	mRenderWindow.reset(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tanx!", sf::Style::Close));
	mRenderWindow->setKeyRepeatEnabled(false);
	mRenderWindow->setActive(true);
	return true;
}

void WindowManager::SetDefaultView()
{
	mRenderTexture->setView(mRenderTexture->getDefaultView());
}

void WindowManager::SetCameraView()
{
	mRenderTexture->setView(mCamera);
}

void WindowManager::SetViewCenter(Vector3 center)
{
	mCamera.setCenter(center.mX, center.mY);
}

sf::View WindowManager::GetCameraView()
{
	return mCamera;
}

void WindowManager::ApplyRenderTextureToWindow()
{
	BlitPass::Apply(*mRenderTexture, *mRenderWindow);
}


