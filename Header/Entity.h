//
// Created by Johnnie on 5/29/2024.
//

#ifndef ALPHA_SQUADRON_HEADER_ENTITY_H_
#define ALPHA_SQUADRON_HEADER_ENTITY_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Entity : public sf::Drawable
{
 public:
	Entity();
 private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite m_sprite;
};

#endif //ALPHA_SQUADRON_HEADER_ENTITY_H_
