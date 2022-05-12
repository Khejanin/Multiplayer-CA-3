#include "RoboCatClientPCH.hpp"

MultiplayerGameState::MultiplayerGameState() : State()
{
	Client::s_instance->EstablishConnection();
}

void MultiplayerGameState::Draw()
{
	RenderManager::sInstance->RenderBackground();
	RenderManager::sInstance->RenderComponents();
	PostEffectsManager::ApplyPostEffects();
	HUD::sInstance->Render();
}

bool MultiplayerGameState::Update(float dt)
{
	SoundManager::sInstance->RemoveStoppedSounds();
	World::sInstance->Update();
	PostEffectsManager::Update();
	return true;
}

bool MultiplayerGameState::HandleEvent(const sf::Event& event)
{
	return true;
}
