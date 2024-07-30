//
// Created by Johnnie Otis on 6/2/24.
//

#include "../Header/PlayerAircraft.h"
#include "../Header/Audio.h"
#include "../Header/Projectile.h"

#define DAMAGE_FLASH_TIME 4.0f
#define DAMAGE_INVINCIBILITY_TIME .3f
#define FIRE_COOLDOWN_TIME 0.2f

PlayerAircraft::PlayerAircraft() : Aircraft(EntityType::Player, true, TextureId::AircraftSpriteSheet, sf::IntRect(240, 298, 52, 12))
{
	setScale(1.0f, 1.0f);
}

void PlayerAircraft::update(float deltaTime)
{
	Aircraft::update(deltaTime);
	handleAnimation(deltaTime);
}

void PlayerAircraft::collision(const Entity* other)
{
	GameSprite::collision(other);

	if(other->getEntityType() == EntityType::Enemy)
	{
		takeDamage(10);
	}
	else if(other->getEntityType() == EntityType::Projectile)
	{
		const auto* projectile = static_cast<const Projectile*>(other);
		if(projectile == nullptr)
		{
			Debug::logError(std::logic_error("Entity set as Projectile type, but is not."));
			return;
		}

		if(projectile->getOwnerType() == EntityType::Enemy)
			takeDamage(20);
	}
}
