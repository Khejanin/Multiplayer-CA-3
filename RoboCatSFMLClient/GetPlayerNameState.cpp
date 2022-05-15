#include "RoboCatClientPCH.hpp"

GetPlayerNameState::GetPlayerNameState() :
	mPleasePutNameText("Please write your desired name and press Enter when done!",
	                   *FontManager::sInstance->GetFont(EFonts::kMain)),
	mPlayerName("Player"),
	mInputPreview("Player", *FontManager::sInstance->GetFont(EFonts::kMain))
{
	mPleasePutNameText.setPosition(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.4);
	Utility::CentreOrigin(mPleasePutNameText);
	mInputPreview.setPosition(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.6);
	Utility::CentreOrigin(mInputPreview);
	if(Client::s_instance->LoadPlayerName())
	{
		mPlayerName = Client::GetPlayerName();
		mInputPreview.setString(mPlayerName);
	}
}

void GetPlayerNameState::Draw()
{
	sf::RenderTexture& tex = *WindowManager::mRenderTexture.get();
	Utility::CentreOrigin(mInputPreview);
	tex.draw(mPleasePutNameText);
	tex.draw(mInputPreview);
}

bool GetPlayerNameState::Update(float dt)
{
	return false;
}

bool GetPlayerNameState::HandleEvent(const sf::Event& event)
{
	//Helped by Paul & Dylan's codebase
	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode == '\b')
		{
			if (!mPlayerName.empty())
				mPlayerName.erase(mPlayerName.size() - 1, 1);
		}
		else if (event.text.unicode != '\n' && event.text.unicode != '\r')
		{
			mPlayerName += static_cast<char>(event.text.unicode);
			mPlayerName = mPlayerName.substr(0, 15);
		}

		mInputPreview.setString(mPlayerName);
	}

	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Enter:
			Client::SetPlayerName(mPlayerName);
			StateStack::PopState();
			StateStack::PushState(EState::kTitle);
			break;
		}
	}
	return false;
}
