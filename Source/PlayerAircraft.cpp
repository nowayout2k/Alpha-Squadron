//
// Created by Johnnie Otis on 6/2/24.
//

#include <SFML/Window/Keyboard.hpp>
#include "../Header/PlayerAircraft.h"
#include "../Header/Audio.h"
#include "../Header/Projectile.h"
#include "../Header/Scene.h"
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

	if(m_fireCooldownRemaining > 0)
		m_fireCooldownRemaining -= deltaTime;
    sf::Vector2f offset = handleInput(deltaTime);
	m_sprite.move(offset);
	handleAnimation(deltaTime);
}

sf::Vector2f PlayerAircraft::handleInput(float deltaTime)
{
    sf::Vector2f offset(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        offset.y -= 800.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        offset.y += 800.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        offset.x -= 800.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        offset.x += 800.f;

    if (offset.x != 0.f && offset.y != 0.f)
    {
        offset.x /= std::sqrt(2.f);
        offset.y /= std::sqrt(2.f);
    }

	offset *= deltaTime;

	adjustOffsetToWindow(offset);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		fireBullet(offset, sf::Vector2f(1000, 0));

    return offset;
}

void PlayerAircraft::adjustOffsetToWindow(sf::Vector2f& offset)
{
    sf::Vector2u windowSize = Game::getWindowSize();
    sf::FloatRect windowBounds(0.f, 0.f, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));

    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();
    playerBounds.left += offset.x;
    playerBounds.top += offset.y;

    if (playerBounds.left < windowBounds.left || playerBounds.left + playerBounds.width > windowBounds.width)
        offset.x = 0.f;
    if (playerBounds.top < windowBounds.top || playerBounds.top + playerBounds.height > windowBounds.height)
        offset.y = 0.f;
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