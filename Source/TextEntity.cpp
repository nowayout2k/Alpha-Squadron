//
// Created by Johnnie Otis on 6/10/24.
//

#include "../Header/TextEntity.h"
#include "../Header/DataCache.h"
TextEntity::TextEntity(Font font, std::string text, unsigned int pixelSize, sf::Color color, sf::Text::Style style, sf::Vector2f position)
{
	m_text = std::make_unique<sf::Text>();
	addDrawable(m_text.get(), true);
	m_font = DataCache::getFont(font);
	m_text->setFont(*m_font.get());
	m_text->setString(text);
	m_text->setCharacterSize(pixelSize);
	m_text->setFillColor(color);
	m_text->setStyle(style);
	m_text->setPosition(position);
}
