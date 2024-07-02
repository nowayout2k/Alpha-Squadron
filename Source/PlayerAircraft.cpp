//
// Created by Johnnie Otis on 6/2/24.
//

#include <SFML/Window/Keyboard.hpp>
#include "../Header/PlayerAircraft.h"
#include "../Header/Audio.h"
#include "../Header/Projectile.h"
#include "../Header/World.h"
#include "../Header/Game.h"

#define DAMAGE_FLASH_TIME 4.0f
#define DAMAGE_INVINCIBILITY_TIME .3f
#define FIRE_COOLDOWN_TIME 0.2f

PlayerAircraft::PlayerAircraft() : Aircraft(EntityType::Player, true, TextureId::AircraftSpriteSheet, sf::IntRect(240, 298, 52, 12))
{
	m_sprite.setScale(4.0f, 4.0f);
    sf::Vector2u windowSize = Game::getWindowSize();
	m_sprite.setPosition(0, (float)windowSize.y / 2.f);
}

void PlayerAircraft::update(float deltaTime)
{
	Aircraft::update(deltaTime);
	adjustToWindow();
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
		fireBullet(sf::Vector2f(0, 0), sf::Vector2f(1000, 0));

    return velocity;
}

void PlayerAircraft::adjustToWindow()
{
	auto pos = getPosition();
    sf::Vector2u windowSize = Game::getWindowSize();
    sf::FloatRect windowBounds(0.f, 0.f, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
	auto globalBounds = getGlobalBounds();
    if (pos.x < windowBounds.left)
		pos.x = 0.f;
    if (pos.x > windowBounds.left + windowBounds.width - globalBounds.width)
		pos.x = windowBounds.left + windowBounds.width - globalBounds.width;
	if (pos.y < -windowBounds.height/2)
		pos.y = -windowBounds.height/2;
	if (pos.y > windowBounds.height/2 - globalBounds.height)
		pos.y = windowBounds.height/2 - globalBounds.height;

	setPosition(pos);
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

		if(projectile->getOwner()->getEntityType() == EntityType::Enemy)
			takeDamage(20);
	}
}
