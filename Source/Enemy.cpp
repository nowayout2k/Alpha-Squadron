//
// Created by Johnnie Otis on 6/1/24.
//

#include "../Header/Enemy.h"
#include "../Header/Player.h"

Enemy::Enemy()
{
    m_texture.loadFromFile("../Assets/Textures/Player.png");
    SetTexture(m_texture);
    SetScale(sf::Vector2f(.1,.1));
    SetPosition(sf::Vector2f(100, 100));
}

void Enemy::Update()
{

}

void Enemy::Collision(const Entity* other)
{
    const Player* player = dynamic_cast<const Player*>(other);
    if (player)
        m_sprite.setColor(sf::Color::Red);
}
