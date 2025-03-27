// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Button.h"
#include "../Headers/Component.h"
#include "../Headers/Utility.h"
#include "../Headers/ResourceManager.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Engine
{
	Button::Button(State::Context context)
		: m_callback()
		, m_sprite(AlphaSquadron::ResourceManager::loadResource(AlphaSquadron::TextureId::UiSpriteSheet))
		, m_text("", AlphaSquadron::ResourceManager::loadResource(FontId::Arnold), 16)
		, m_isToggle(false)
		, m_audio(*context.Audio)
	{
		changeTexture(Normal);
		Utility::centerOrigin(m_sprite);
	}

	void Button::setCallback(Callback callback)
	{
		m_callback = std::move(callback);
	}

	void Button::setText(const int size, const std::string& text)
	{
		m_text.setString(text);
		m_text.setCharacterSize(size);
		Utility::centerOrigin(m_text);
	}

	void Button::setToggle(bool flag)
	{
		m_isToggle = flag;
	}

	bool Button::isSelectable() const
	{
		return true;
	}

	void Button::select()
	{
		Component::select();
		changeTexture(Selected);
	}

	void Button::deselect()
	{
		Component::deselect();
		changeTexture(Normal);
	}

	void Button::activate()
	{
		Component::activate();
		if (m_isToggle)
			changeTexture(Pressed);

		if (m_callback)
			m_callback();

		if (!m_isToggle)
			deactivate();

		m_audio.playSound(AlphaSquadron::SoundFxId::ButtonClick);
	}

	void Button::deactivate()
	{
		Component::deactivate();
		if (m_isToggle)
		{
			if (isSelected())
				changeTexture(Selected);
			else
				changeTexture(Normal);
		}
	}

	void Button::handleEvent(const sf::Event&)
	{
		// No additional event handling required.
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(m_sprite, states);
		target.draw(m_text, states);
	}

	void Button::changeTexture(Type buttonType)
	{
		sf::IntRect textureRect;
		if (buttonType == Normal)
			textureRect = sf::IntRect(0, 0, 208, 64);
		else if (buttonType == Selected)
			textureRect = sf::IntRect(223, 0, 208, 64);
		else
			textureRect = sf::IntRect(445, 0, 208, 64);
		m_sprite.setTextureRect(textureRect);
	}

	void Button::setButtonOrigin(const float x, const float y)
	{
		m_sprite.setOrigin(x, y);
		sf::FloatRect spriteBounds = m_sprite.getLocalBounds();
		sf::FloatRect textBounds = m_text.getLocalBounds();
		m_text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
		m_text.setPosition(spriteBounds.width / 2.f, spriteBounds.height / 2.f);
	}
}
