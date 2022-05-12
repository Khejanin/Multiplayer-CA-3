#include "RoboCatClientPCH.hpp"

MultiplayerGameState::MultiplayerGameState() : State()
{
	Client::s_instance->EstablishConnection();
}

void MultiplayerGameState::Draw()
{
	RenderManager::sInstance->RenderBackground();
	RenderManager::sInstance->RenderComponents();

	HUD::sInstance->Render();
}

bool MultiplayerGameState::Update(float dt)
{
	World::sInstance->Update();
	return true;
}

bool MultiplayerGameState::HandleEvent(const sf::Event& event)
{
	return true;
}
