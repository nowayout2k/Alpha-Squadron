//
// Created by Johnnie Otis on 6/1/24.
//

#include "../Header/EnemyAircraft.h"
#include "../Header/PlayerAircraft.h"
#include "../Header/Projectile.h"
#include "../Header/World.h"
#include "../Header/Game.h"

EnemyAircraft::EnemyAircraft(bool hasCollision, sf::Vector2f position) : Aircraft(EntityType::Enemy, hasCollision, TextureId::EnemiesSpriteSheet,
                                               sf::IntRect(70, 200, 25, 12))
{
    setScale(sf::Vector2f(-4,4));
	setPosition(position);
	m_health = 100;
	m_fireCooldownRemaining = 4;
}

bool goUp = true;

void EnemyAircraft::update(float deltaTime)
{
	Aircraft::update(deltaTime);

	if(m_health <= 0)
	{
		destroy();
		return;
	}

	sf::Vector2f velocity;
	sf::Vector2u windowSize = Game::getWindowSize();
	sf::FloatRect windowBounds(0.f, 0.f, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
	auto pos = getPosition();
	if(goUp)
	{
		if(pos.y > windowBounds.height)
			goUp = false;
		velocity = sf::Vector2f(0, 500);
	}
	else
	{
		if(pos.y < 0)
			goUp = true;
		velocity = sf::Vector2f(0, -500);
	}

	if(m_fireCooldownRemaining > 0)
	{
		m_fireCooldownRemaining -= deltaTime;
	}
	else
	{
		fireBullet(getPosition(), sf::Vector2f(-1000, 0));
	}

	setVelocity(velocity);
}

void EnemyAircraft::collision(const Entity* other)
{
	GameSprite::collision(other);

	if(other->getEntityType() == EntityType::Player)
	{
		takeDamage(m_health);
	}
	else if(other->getEntityType() == EntityType::Projectile)
	{
		const auto* projectile = static_cast<const Projectile*>(other);
		if(projectile == nullptr)
		{
			Debug::logError(std::logic_error("Entity set as Projectile type, but is not."));
			return;
		}

		if(projectile->getOwnerType() == EntityType::Player)
			takeDamage(50);
	}
}
