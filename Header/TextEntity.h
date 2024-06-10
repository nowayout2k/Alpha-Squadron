//
// Created by Johnnie Otis on 6/10/24.
//

#ifndef ALPHA_SQUADRON_HEADER_TEXTENTITY_H_
#define ALPHA_SQUADRON_HEADER_TEXTENTITY_H_

#include <SFML/Graphics/Text.hpp>
#include "DrawableEntity.h"
#include "Font.h"

class TextEntity : public DrawableEntity
{
 public:
	TextEntity(Font font, std::string text, unsigned int pixelSize, sf::Color color, sf::Text::Style style, sf::Vector2f position);
 protected:

 private:
	std::unique_ptr<sf::Text> m_text;
	std::shared_ptr<sf::Font> m_font;
};

#endif //ALPHA_SQUADRON_HEADER_TEXTENTITY_H_
