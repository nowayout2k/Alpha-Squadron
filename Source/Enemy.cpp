//
// Created by Johnnie Otis on 6/1/24.
//

#include "../Header/Enemy.h"
#include "../Header/Player.h"

Enemy::Enemy(bool hasCollision) : SpriteEntity(hasCollision, "../Assets/Textures/EnemiesSpriteSheet.png",
                                               sf::IntRect(70, 200, 25, 12))
{
    setScale(sf::Vector2f(2,2));
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
