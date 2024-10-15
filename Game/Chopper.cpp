//
// Created by Johnnie Otis on 6/1/24.
//

#include "Chopper.h"
#include "../Engine/Projectile.h"
#include "../Engine/World.h"

Chopper::Chopper(bool hasCollision, sf::Vector2f position, NodeType nodeType) : Aircraft(hasCollision, TextureId::EnemiesSpriteSheet,
                                               sf::IntRect(70, 200, 25, 12)),
											   m_nodeType(Aircraft::getNodeType() | (unsigned int)nodeType)
{
    setScale(sf::Vector2f(-1,1));
	setPosition(position);
	setHealth(100);
}

bool goUp = true;

void Chopper::update(float deltaTime)
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

void Chopper::collision(const Entity* other)
{
	GameSprite::collision(other);

	if((other->getNodeType() & (unsigned int)NodeType::Player) > 0)
	{
		takeDamage(getHealth());
	}
	else if((other->getNodeType() & (unsigned int)NodeType::Projectile) > 0)
	{
		const auto* projectile = static_cast<const Projectile*>(other);
		if(projectile == nullptr)
		{
			Debug::logError("Entity set as Projectile type, but is not.");
			return;
		}

		if(projectile->getOwnerType() == NodeType::Player)
			takeDamage(50);
	}
}
