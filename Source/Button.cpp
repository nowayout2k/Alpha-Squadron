// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Button.h"
#include "../Headers/Component.h"
#include "../Headers/Utility.h"
#include "../Headers/ResourceManager.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	Button::Button() : m_normalTexture(ResourceManager::loadResource(TextureId::BlueButtonIdle)), m_pressedTexture(ResourceManager::loadResource(TextureId::BlueButtonClicked)), m_selectedTexture(ResourceManager::loadResource(TextureId::MagentaButtonIdle))
	{
		m_sprite.setTexture(m_normalTexture);
		m_text.setFont(ResourceManager::loadResource(FontId::Gamer));
		m_text.setFillColor(sf::Color::White);
		Utility::centerOrigin(m_sprite);
	}

	void Button::select()
	{
		Component::select();
		m_sprite.setTexture(m_selectedTexture);
	}

	void Button::deselect()
	{
		Component::deselect();
		m_sprite.setTexture(m_normalTexture);
	}

	void Button::activate()
	{
		Component::activate();
		if (m_isToggle)
			m_sprite.setTexture(m_pressedTexture);
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
				m_sprite.setTexture(m_selectedTexture);
			else
				m_sprite.setTexture(m_normalTexture);
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
