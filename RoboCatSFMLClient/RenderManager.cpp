#include "RoboCatClientPCH.hpp"

std::unique_ptr<RenderManager> RenderManager::sInstance;

RenderManager::RenderManager()
{
	view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	//Prepare the background
	sf::Texture& texture = *TextureManager::sInstance->GetTexture(ETextures::kBackground);
	sf::IntRect textureRect(0, 0, WORLD_WIDTH/5, WORLD_HEIGHT/5);
	//Tile the texture to cover our world
	texture.setRepeated(true);
	mBackground = std::make_unique<sf::Sprite>(sf::Sprite(texture, textureRect));
	(*mBackground).setScale(5,5);
	WindowManager::sInstance->setView(view);
}

void RenderManager::StaticInit()
{
	sInstance.reset(new RenderManager());
}

void RenderManager::AddComponent(SpriteComponent* inComponent)
{
	mComponents.emplace_back(inComponent);
}

void RenderManager::RemoveComponent(SpriteComponent* inComponent)
{
	int index = GetComponentIndex(inComponent);

	if (index != -1)
	{
		int lastIndex = mComponents.size() - 1;
		if (index != lastIndex)
		{
			mComponents[index] = mComponents[lastIndex];
		}
		mComponents.pop_back();
	}
}

int RenderManager::GetComponentIndex(SpriteComponent* inComponent) const
{
	for (int i = 0, c = mComponents.size(); i < c; ++i)
	{
		if (mComponents[i] == inComponent)
		{
			return i;
		}
	}

	return -1;
}

void RenderManager::RenderBackground()
{
	WindowManager::sInstance->draw(*mBackground);
}


//this part that renders the world is really a camera-
//in a more detailed engine, we'd have a list of cameras, and then render manager would
//render the cameras in order
void RenderManager::RenderComponents()
{
	//Get the logical viewport so we can pass this to the SpriteComponents when it's draw time
	for (SpriteComponent* c : mComponents)
	{
		WindowManager::sInstance->draw(c->GetSprite());
	}
	for (auto goIt = World::sInstance->GetGameObjects().begin(), end = World::sInstance->GetGameObjects().end(); goIt != end; ++goIt)
	{
		auto bounds = (*goIt)->GetBounds();
		sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
		rect.setPosition((*goIt)->GetPosition().mX, (*goIt)->GetPosition().mY);
		rect.setOutlineThickness(1.0f);
		rect.setOutlineColor(sf::Color::Green);
		rect.setFillColor(sf::Color::Transparent);
		WindowManager::sInstance->draw(rect);
	}
}

void RenderManager::Render()
{
	//
	// Clear the back buffer
	//
	WindowManager::sInstance->clear(sf::Color(100, 149, 237, 255));
	WindowManager::SetCameraView();

	StateStack::sInstance->Draw();

	/* Comment out
	RenderManager::sInstance->RenderComponents();

	HUD::sInstance->Render();
	*/
	//
	// Present our back buffer to our front buffer
	//
	WindowManager::sInstance->display();
}
