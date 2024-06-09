//
// Created by Johnnie Otis on 6/8/24.
//

#include "../Header/Bullet.h"

Bullet::Bullet(Entity* owner, sf::Vector2f spawnPos) : m_owner(owner), SpriteEntity(true,
	"../Assets/Textures/AircraftSpriteSheet.png",
	sf::IntRect(376, 108, 10, 12))
{
	setScale(2.0f, 2.0f);
	setPosition(spawnPos);
	m_hasCollision = true;
}

void Bullet::update(float deltaTime)
{
	sf::Vector2u windowSize = WindowManager::getSize();
	m_sprite->move(sf::Vector2f(500, 0)*deltaTime);
}

void Bullet::collision(const Entity* other)
{
	SpriteEntity::collision(other);
}
