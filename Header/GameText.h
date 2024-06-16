//
// Created by Johnnie Otis on 6/10/24.
//

#ifndef ALPHA_SQUADRON_HEADER_GAMETEXT_H_
#define ALPHA_SQUADRON_HEADER_GAMETEXT_H_

#include <SFML/Graphics/Text.hpp>
#include "FontId.h"
#include "Entity.h"
#include "ResourceCache.h"

class GameText : public Entity
{
 public:
	GameText(FontId fontType, std::string text, unsigned int pixelSize, sf::Color color, sf::Text::Style style, sf::Vector2f position)
		: m_fontType(fontType), Entity(false)
	{
		m_text.setString(text);
		m_text.setCharacterSize(pixelSize);
		m_text.setFillColor(color);
		m_text.setStyle(style);
		m_text.setPosition(position);
		m_text.getGlobalBounds();
	}

	virtual void update(float deltaTime) override { if(!isActive()) return; }
	virtual void render(sf::RenderWindow& renderWindow, sf::RenderStates states) override
	{
		if(!isActive())
			return;
		renderWindow.draw(m_text, states);
	}

	void loadResources() override
	{
		m_font = ResourceCache::getFont(m_fontType);
		m_text.setFont(*m_font);
	};

	void collision(const Entity* other) override { if(!hasCollision()) return; }
	bool isColliding(const sf::Rect<float>& bounds) const override
	{
		if(!hasCollision())
			return false;

		return m_text.getGlobalBounds().intersects(bounds);
	}
 private:
	sf::Font* m_font;
	sf::Text m_text;
	FontId m_fontType;
};

#endif //ALPHA_SQUADRON_HEADER_GAMETEXT_H_
