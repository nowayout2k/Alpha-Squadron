//
// Created by Johnnie Otis on 6/1/24.
//

#include "../Header/Enemy.h"
#include "../Header/Player.h"
#include "../Header/Bullet.h"
#include "../Header/GameManager.h"

Enemy::Enemy(bool hasCollision, sf::Vector2f position) : SpriteEntity(hasCollision, "../Assets/Textures/EnemiesSpriteSheet.png",
                                               sf::IntRect(70, 200, 25, 12))
{
    setScale(sf::Vector2f(-2,2));
    setPosition(position);
	m_health = 100;
	m_fireCooldownRemaining = 4;
}

bool goUp = false;
void Enemy::update(float deltaTime)
{
	if(m_health <= 0)
	{
		destroy();
		return;
	}

	Entity::update(deltaTime);

	sf::Vector2f offset;
	auto windowSize = WindowManager::getSize();
	if(goUp)
	{
		if(getPosition().y <= 0)
			goUp = false;
		offset = sf::Vector2f(0, -100);

	}
	else
	{
		if(getPosition().y >= windowSize.y)
			goUp = true;
		offset = sf::Vector2f(0, 100);
	}

	offset *= deltaTime;

	if(m_fireCooldownRemaining > 0)
	{
		m_fireCooldownRemaining -= deltaTime;
	}
	else
	{
		fireBullet(offset);
	}

	move(offset);
}

void Enemy::collision(const Entity* other)
{
	SpriteEntity::collision(other);
    const Player* player = dynamic_cast<const Player*>(other);
	const Bullet* bullet = dynamic_cast<const Bullet*>(other);
    if ((player && player->hasCollision()))
	{
		m_health-=100;
	}
	else if (bullet && bullet->hasCollision())
	{
		const Player* playerOwner = dynamic_cast<const Player*>(bullet->getOwner());
		if(playerOwner)
			m_health-=100;
	}
}

void Enemy::fireBullet(sf::Vector2f offset)
{
	auto spawnPos = getPosition() + offset;
	GameManager::addEntity(std::move(std::make_unique<Bullet>(this, spawnPos, sf::Vector2f(-500, 0))));
	m_fireCooldownRemaining = FIRE_COOLDOWN_TIME;
}
