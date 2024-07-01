//
// Created by Johnnie Otis on 6/1/24.
//

#include "../Header/EnemyAircraft.h"
#include "../Header/PlayerAircraft.h"
#include "../Header/Projectile.h"
#include "../Header/Scene.h"
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

	sf::Vector2f offset;
	auto windowSize = Game::getWindowSize();

	if(goUp)
	{
		if(m_sprite.getPosition().y <= 0)
			goUp = false;
		offset = sf::Vector2f(0, -500);

	}
	else
	{
		if(m_sprite.getPosition().y >= windowSize.y)
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

	m_sprite.move(offset);
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