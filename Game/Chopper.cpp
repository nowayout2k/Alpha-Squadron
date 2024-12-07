//
// Created by Johnnie Otis on 6/1/24.
//

#include "Chopper.h"
#include "../Engine/Projectile.h"
#include "../Engine/World.h"

Chopper::Chopper(bool hasCollision, sf::Vector2f position, NodeType nodeType, sf::Vector2f scale) :
	Aircraft(hasCollision, scale, position),
	m_nodeType(Aircraft::getNodeType() | (unsigned int)nodeType)
{
}

void Chopper::update(float deltaTime)
{
	Aircraft::update(deltaTime);

	if(getHealth() <= 0)
	{
		destroy();
		return;
	}
	fireBullet(sf::Vector2f(1000, 0));
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
