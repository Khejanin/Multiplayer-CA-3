#include "RoboCatShared.hpp"

#include "SFML\Graphics.hpp"

#include "Animation.hpp"
//Utility depends on Animation
#include "Utility.hpp"

//Enums
#include "ETextures.hpp"
#include "ESounds.hpp"
#include "EFonts.hpp"
#include "EState.hpp"
#include "EButton.hpp"

#include "InputManager.hpp"
#include "SpriteComponent.hpp"
#include "PlayerSpriteComponent.hpp"
#include "TextureManager.hpp"
#include "SoundManager.hpp"
#include "FontManager.hpp"
#include "RenderManager.hpp"
#include "WindowManager.hpp"

#include "RoboCatClient.hpp"
#include "MouseClient.hpp"
#include "YarnClient.hpp"
#include "TankClient.hpp"
#include "ProjectileClient.hpp"
#include "TileClient.hpp"

#include "HUD.hpp"

//GUI
#include "Component.hpp"
#include "Container.hpp"
#include "Button.hpp"

//States
#include "State.hpp"
#include "StateStack.hpp"

#include "TitleState.hpp"
#include "MenuState.hpp"
#include "MultiplayerGameState.hpp"

#include "ReplicationManagerClient.hpp"
#include "NetworkManagerClient.hpp"
#include "Client.hpp"

