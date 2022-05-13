#include "RoboCatClientPCH.hpp"

std::unique_ptr<Client> Client::s_instance;

bool Client::StaticInit()
{
	// Create the Client pointer first because it initializes SDL
	Client* client = new Client();
	InputManager::StaticInit();

	WindowManager::StaticInit();
	FontManager::StaticInit();
	TextureManager::StaticInit();
	ShaderManager::StaticInit();
	PostEffectsManager::StaticInit();
	RenderManager::StaticInit();
	SoundManager::StaticInit();

	StateStack::StaticInit();
	HUD::StaticInit();

	s_instance.reset(client);

	RegisterStates();

	StateStack::sInstance->PushState(EState::kTitle);

	return true;
}

Client::Client()
{
}

void Client::DoFrame()
{
	InputManager::sInstance->Update();

	Engine::DoFrame();

	StateStack::sInstance->Update(Timing::sInstance.GetDeltaTime());

	if(is_connected)
		NetworkManagerClient::sInstance->ProcessIncomingPackets();

	RenderManager::sInstance->Render();

	if(is_connected)
		NetworkManagerClient::sInstance->SendOutgoingPackets();
}

void Client::HandleEvent(sf::Event& p_event)
{
	switch (p_event.type)
	{
	case sf::Event::KeyPressed:
		InputManager::sInstance->HandleInput(EIA_Pressed, p_event.key.code);
		break;
	case sf::Event::KeyReleased:
		InputManager::sInstance->HandleInput(EIA_Released, p_event.key.code);
		break;
	default:
		break;
	}

	StateStack::sInstance->HandleEvent(p_event);
}

bool Client::PollEvent(sf::Event& p_event)
{
	return WindowManager::mRenderWindow->pollEvent(p_event);
}

void Client::EstablishConnection()
{
	GameObjectRegistry::sInstance->RegisterCreationFunction('TANK', TankClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('PROJ', ProjectileClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('TILE', TileClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('PICK', PickupClient::StaticCreate);
	GameObjectRegistry::sInstance->RegisterCreationFunction('EXPL', Explosion::StaticCreate);

	string destination = StringUtils::GetCommandLineArg(1);
	string name = StringUtils::GetCommandLineArg(2);

	SocketAddressPtr serverAddress = SocketAddressFactory::CreateIPv4FromString(destination);

	NetworkManagerClient::StaticInit(*serverAddress, name);

	is_connected = true;
}

void Client::CloseConnection()
{
	is_connected = false;
}

void Client::RegisterStates()
{
	StateStack::sInstance->RegisterState<TitleState>(EState::kTitle);
	StateStack::sInstance->RegisterState<MenuState>(EState::kMenu);
	StateStack::sInstance->RegisterState<MultiplayerGameState>(EState::kJoinGame);
}
