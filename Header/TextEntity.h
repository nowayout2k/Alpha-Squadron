//
// Created by Johnnie Otis on 6/10/24.
//

#ifndef ALPHA_SQUADRON_HEADER_TEXTENTITY_H_
#define ALPHA_SQUADRON_HEADER_TEXTENTITY_H_

#include <SFML/Graphics/Text.hpp>
#include "Font.h"
#include "Entity.h"
#include "DataCache.h"

class TextEntity : public sf::Text, public Entity
{
 public:
	TextEntity(Font font, std::string text, unsigned int pixelSize, sf::Color color, sf::Text::Style style, sf::Vector2f position)
	{
		m_font = DataCache::getFont(font);
		setFont(*m_font.get());
		setString(text);
		setCharacterSize(pixelSize);
		setFillColor(color);
		setStyle(style);
		setPosition(position);
	}
 protected:

 private:
	std::shared_ptr<sf::Font> m_font;
};

#endif //ALPHA_SQUADRON_HEADER_TEXTENTITY_H_
