//
// Created by Johnnie Otis on 10/13/24.
//

#include "Button.h"
#include "Component.h"
#include "Utility.h"
#include "ResourceManager.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
	Button::Button() : m_normalTexture(ResourceManager::loadResource(TextureId::BlueButtonIdle)), m_pressedTexture(ResourceManager::loadResource(TextureId::BlueButtonClicked)), m_selectedTexture(ResourceManager::loadResource(TextureId::MagentaButtonIdle))
	{
		m_sprite.setTexture(m_normalTexture);
		m_text.setFont(ResourceManager::loadResource(FontId::Gamer));
		m_text.setFillColor(sf::Color::White);
		auto dimensions = m_normalTexture.getSize() / 2u;
		m_text.setPosition(sf::Vector2f(dimensions));
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

	void Button::setText(const std::string& text)
	{
		m_text.setString(text);
		Utility::centerOrigin(m_text);
	}

	void Button::setToggle(bool flag)
	{
		m_isToggle = flag;
	}

}