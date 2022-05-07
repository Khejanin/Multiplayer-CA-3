#include "RoboCatClientPCH.hpp"

namespace GUI
{
	Button::Button()
	: m_sprite(*TextureManager::sInstance->GetTexture(ETextures::kButtonNormal))
	, m_text("",*FontManager::sInstance->GetFont(EFonts::kMain), 16)
	, m_is_toggle(false)
	{
		ChangeTexture(EButton::Normal);
		sf::FloatRect bounds = m_sprite.getLocalBounds();
		m_text.setPosition(bounds.width / 2, bounds.height / 2);

	}

	void Button::SetCallback(Callback callback)
	{
		m_callback = std::move(callback);
	}

	void Button::SetText(const std::string& text)
	{
		m_text.setString(text);
		Utility::CentreOrigin(m_text);
	}

	void Button::SetToggle(bool flag)
	{
		m_is_toggle = flag;
	}

	bool Button::IsSelectable() const
	{
		return true;
	}

	void Button::Select()
	{
		Component::Select();
		ChangeTexture(EButton::Selected);
	}

	void Button::Deselect()
	{
		Component::Deselect();
		ChangeTexture(EButton::Normal);
	}

	void Button::Activate()
	{
		Component::Activate();
		//If toggle then show button is pressed or toggled
		if(m_is_toggle)
		{
			ChangeTexture(EButton::Pressed);
		}
		if(m_callback)
		{
			m_callback();
		}
		if(!m_is_toggle)
		{
			Deactivate();
		}
		SoundManager::sInstance->Play(ESounds::kButton);
	}

	void Button::Deactivate()
	{
		Component::Deactivate();
		if(m_is_toggle)
		{
			if(IsSelected())
			{
				ChangeTexture(EButton::Selected);
			}
			else
			{
				ChangeTexture(EButton::Normal);
			}
		}
	}

	void Button::HandleEvent(const sf::Event& event)
	{
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(m_sprite, states);
		target.draw(m_text, states);
	}

	void Button::ChangeTexture(EButton EButton)
	{
		sf::IntRect textureRect(0, 50 * static_cast<int>(EButton), 200, 50);
		m_sprite.setTextureRect(textureRect);
	}
}
