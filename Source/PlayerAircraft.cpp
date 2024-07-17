//
// Created by Johnnie Otis on 6/2/24.
//

#include <SFML/Window/Keyboard.hpp>
#include "../Header/PlayerAircraft.h"
#include "../Header/Audio.h"
#include "../Header/Projectile.h"

#define DAMAGE_FLASH_TIME 4.0f
#define DAMAGE_INVINCIBILITY_TIME .3f
#define FIRE_COOLDOWN_TIME 0.2f

PlayerAircraft::PlayerAircraft() : Aircraft(EntityType::Player, true, TextureId::AircraftSpriteSheet, sf::IntRect(240, 298, 52, 12))
{
	setScale(4.0f, 4.0f);
}

void PlayerAircraft::update(float deltaTime)
{
	Aircraft::update(deltaTime);

	if(m_fireCooldownRemaining > 0)
		m_fireCooldownRemaining -= deltaTime;
	setVelocity(handleInput(deltaTime));
	handleAnimation(deltaTime);
}

sf::Vector2f PlayerAircraft::handleInput(float deltaTime)
{
    sf::Vector2f velocity(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		velocity.y -= 800.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		velocity.y += 800.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		velocity.x -= 800.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		velocity.x += 800.f;

    if (velocity.x != 0.f && velocity.y != 0.f)
    {
		velocity.x /= std::sqrt(2.f);
		velocity.y /= std::sqrt(2.f);
    }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		fireBullet(getPosition(), sf::Vector2f(1000, 0));

    return velocity;
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
