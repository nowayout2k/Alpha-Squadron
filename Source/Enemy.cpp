//
// Created by Johnnie Otis on 6/1/24.
//

#include "../Header/Enemy.h"
#include "../Header/Player.h"
#include "../Header/Projectile.h"
#include "../Header/Scene.h"
#include "../Header/Window.h"

Enemy::Enemy(bool hasCollision, sf::Vector2f position) : Character(hasCollision, "../Assets/Textures/EnemiesSpriteSheet.png",
                                               sf::IntRect(70, 200, 25, 12))
{
    setScale(sf::Vector2f(-4,4));
    setPosition(position);
	m_health = 100;
	m_fireCooldownRemaining = 4;
}

bool goUp = true;

void Enemy::update(float deltaTime)
{
	if(m_health <= 0)
	{
		destroy();
		return;
	}

	Entity::update(deltaTime);

	sf::Vector2f offset;
	auto windowSize = Window::getSize();

	if(goUp)
	{
		if(getPosition().y <= 0)
			goUp = false;
		offset = sf::Vector2f(0, -500);

	}
	else
	{
		if(getPosition().y >= windowSize.y)
			goUp = true;
		offset = sf::Vector2f(0, 500);
	}

	offset *= deltaTime;

	if(m_fireCooldownRemaining > 0)
	{
		m_fireCooldownRemaining -= deltaTime;
	}
	else
	{
		fireBullet(offset, sf::Vector2f(-1000, 0));
	}

	move(offset);
}

void Enemy::collision(const Entity* other)
{
	SpriteEntity::collision(other);
    const auto* player = dynamic_cast<const Player*>(other);
	const auto* bullet = dynamic_cast<const Projectile*>(other);
    if (player && player->hasCollision())
	{
		takeDamage(m_health);
	}
	else if (bullet && bullet->hasCollision())
	{
		const auto* playerOwner = dynamic_cast<const Player*>(bullet->getOwner());
		if(playerOwner)
			takeDamage(50);
	}
}
