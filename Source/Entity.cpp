//
// Created by Johnnie on 5/29/2024.
//

#include "../Header/Entity.h"
#include "../Header/Input.h"
#include <SFML/Graphics/Texture.hpp>

Entity::Entity()
{
    m_texture.loadFromFile("../Assets/Textures/Player.png");
    m_sprite.setScale(.1, .1);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(100, 25);

    Input::SubscribeKey(sf::Keyboard::Key::W, [this]() { m_sprite.move(0, -10); });
    Input::SubscribeKey(sf::Keyboard::Key::S, [this]() { m_sprite.move(0, 10); });
    Input::SubscribeKey(sf::Keyboard::Key::A, [this]() { m_sprite.move(-10, 0); });
    Input::SubscribeKey(sf::Keyboard::Key::D, [this]() { m_sprite.move(10, 0); });
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

