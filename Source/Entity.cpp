//
// Created by Johnnie on 5/29/2024.
//

#include "../Header/Entity.h"
#include <SFML/Graphics/Texture.hpp>

Entity::Entity()
{
	sf::Texture texture;
	texture.loadFromFile("../Assets/Textures/Player.png");

	m_sprite.setTexture(texture);
	m_sprite.setPosition(100, 25);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

