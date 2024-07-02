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
    m_sprite.setScale(sf::Vector2f(-4,4));
	m_sprite.setPosition(position);
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
    auto globalBounds = getGlobalBounds();
	auto pos = getPosition();
	if(goUp)
	{
		if(pos.y > windowBounds.height - globalBounds.height)
			goUp = false;
		velocity = sf::Vector2f(0, 500);
	}
	else
	{
		if(pos.y < -windowBounds.height)
			goUp = true;
		velocity = sf::Vector2f(0, -500);
	}

	if(m_fireCooldownRemaining > 0)
	{
		m_fireCooldownRemaining -= deltaTime;
	}
	else
	{
		fireBullet(sf::Vector2f(-m_sprite.getLocalBounds().width, -m_sprite.getLocalBounds().height), sf::Vector2f(-1000, 0));
	}

	setVelocity(velocity);
}

void EnemyAircraft::collision(const Entity* other)
{
	GameSprite::collision(other);
    const auto* player = dynamic_cast<const PlayerAircraft*>(other);
	const auto* bullet = dynamic_cast<const Projectile*>(other);
    if (player && player->hasCollision())
	{
		takeDamage(m_health);
	}
	else if (bullet && bullet->hasCollision())
	{
		const auto* playerOwner = dynamic_cast<const PlayerAircraft*>(bullet->getOwner());
		if(playerOwner)
			takeDamage(50);
	}
}
