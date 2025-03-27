// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef GAMETEXT_H_
#define GAMETEXT_H_

#include "ResourceManager.h"
#include "Utility.h"

#include <SFML/Graphics/Text.hpp>

/**
 * @file GameText.h
 * @brief Declaration of the GameText class.
 *
 * The GameText class is a WorldNode that displays text using a specified font.
 * It handles loading of the font resource, centers the text's origin, and manages rendering.
 */
class GameText : public WorldNode
{
 public:
	/**
	 * @brief Constructs a GameText object.
	 * @param fontType The font identifier.
	 * @param text The string to display.
	 * @param pixelSize The character size in pixels.
	 * @param color The fill color of the text.
	 * @param style The text style.
	 * @param position The initial position of the text.
	 */
	GameText(FontId fontType, std::string text, unsigned int pixelSize, sf::Color color, sf::Text::Style style, sf::Vector2f position)
		: m_fontType(fontType), WorldNode(false)
	{
		setString(text);
		m_text.setCharacterSize(pixelSize);
		m_text.setFillColor(color);
		m_text.setStyle(style);
		m_text.setPosition(position);
		m_text.getGlobalBounds(); // Force bounds calculation.
	}

	/**
	 * @brief Retrieves the node type for GameText.
	 * @return The combined node type flags.
	 */
	virtual unsigned int getNodeType() const override { return WorldNode::getNodeType() | static_cast<unsigned int>(NodeType::Text); }

	/**
	 * @brief Gets the bounding rectangle of the text in world coordinates.
	 * @return A rectangle representing the text's bounds.
	 */
	sf::Rect<float> getBoundingRect() const override
	{
		sf::FloatRect bounds = m_text.getGlobalBounds();
		return getTransform().transformRect(bounds);
	}

	/**
	 * @brief Sets the text string and centers its origin.
	 * @param text The string to display.
	 */
	void setString(const std::string& text)
	{
		m_text.setString(text);
		Utility::centerOrigin(m_text);
	}

	/**
	 * @brief Updates the text (no dynamic updates needed).
	 * @param deltaTime The elapsed time.
	 * @param commands The command queue.
	 */
	void update(sf::Time deltaTime, CommandQueue& commands) override { if (!isActive()) return; }

	/**
	 * @brief Renders the text.
	 * @param renderTarget The render target.
	 * @param states The render states.
	 */
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override
	{
		if (!isActive())
			return;
		renderTarget.draw(m_text, states);
	}

	/**
	 * @brief Loads the font resource for the text.
	 */
	void loadResources() override
	{
		m_text.setFont(ResourceManager::loadResource(m_fontType));
	}

 private:
	sf::Text m_text;   // SFML text object.
	FontId m_fontType; // Font identifier.
};

#endif // GAMETEXT_H_
