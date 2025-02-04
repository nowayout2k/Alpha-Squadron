// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Button.h"
#include "../Headers/Component.h"
#include "../Headers/Utility.h"
#include "../Headers/ResourceManager.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	Button::Button(sf::IntRect normalTextureRect, sf::IntRect pressedTextureRect, sf::IntRect selectedTextureRect) :
						m_normalTextureRect(normalTextureRect),
						m_pressedTextureRect(pressedTextureRect),
						m_selectedTextureRect(selectedTextureRect),
						m_isToggle(false)
	{
		m_sprite.setTexture(ResourceManager::loadResource(TextureId::UiSpriteSheet));
		m_sprite.setTextureRect(m_normalTextureRect);
		m_text.setFont(ResourceManager::loadResource(FontId::Arnold));
		m_text.setFillColor(sf::Color::White);
		Utility::centerOrigin(m_sprite);
	}

	void Button::select()
	{
		Component::select();
		m_sprite.setTextureRect(m_selectedTextureRect);
	}

	void Button::deselect()
	{
		Component::deselect();
		m_sprite.setTextureRect(m_normalTextureRect);
	}

	void Button::activate()
	{
		Component::activate();
		if (m_isToggle)
			m_sprite.setTextureRect(m_pressedTextureRect);
		if (m_callback)
			m_callback();
		if (!m_isToggle)
			deactivate();
	}

	void Button::deactivate()
	{
		Component::deactivate();
		if (m_isToggle)
		{
			if (Component::isSelected())
				m_sprite.setTextureRect(m_selectedTextureRect);
			else
				m_sprite.setTextureRect(m_normalTextureRect);
		}
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(m_sprite, states);
		target.draw(m_text, states);
	}

	void Button::setCallback(std::function<void()> callback)
	{
		m_callback = std::move(callback);
	}

	void Button::setText(const unsigned int size, const std::string& text)
	{
		m_text.setCharacterSize(size);
		m_text.setString(text);
		Utility::centerOrigin(m_text);
	}

	void Button::setToggle(bool flag)
	{
		m_isToggle = flag;
	}

}
