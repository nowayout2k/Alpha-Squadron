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
    setScale(sf::Vector2f(-1,1));
	setPosition(position);
	setHealth(100);
}

bool goUp = true;

void EnemyAircraft::update(float deltaTime)
{
	Aircraft::update(deltaTime);

	if(getHealth() <= 0)
	{
		destroy();
		return;
	}

	auto pos = getPosition();
	if(goUp)
	{
		if(pos.y > 1000)
			goUp = false;
		setVelocity(0, 500);
	}
	else
	{
		if(pos.y < 0)
			goUp = true;
		setVelocity(0, -500);
	}

	fireBullet(sf::Vector2f(-1000, 0));
}

void EnemyAircraft::collision(const Entity* other)
{
	GameSprite::collision(other);

	if(other->getEntityType() == EntityType::Player)
	{
		takeDamage(getHealth());
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
