//
// Created by Johnnie Otis on 6/1/24.
//

#include "../Header/Enemy.h"
#include "../Header/Player.h"

Enemy::Enemy(std::string pathToTexture, bool hasCollision) : SpriteEntity(pathToTexture, hasCollision)
{
    setScale(sf::Vector2f(.1,.1));
    setPosition(sf::Vector2f(100, 100));
}

void Enemy::Update(float deltaTime)
{

}

void Enemy::Collision(const Entity* other)
{
    SpriteEntity::Collision(other);
    const Player* player = dynamic_cast<const Player*>(other);
    if (player)
        m_sprite->setColor(sf::Color::Red);
}
