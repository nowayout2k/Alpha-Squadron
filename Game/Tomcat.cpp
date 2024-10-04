//
// Created by Johnnie Otis on 6/2/24.
//

#include "Tomcat.h"
#include "../Engine/Audio.h"
#include "../Engine/Projectile.h"

#define DAMAGE_FLASH_TIME 4.0f
#define DAMAGE_INVINCIBILITY_TIME .3f
#define FIRE_COOLDOWN_TIME 0.2f

Tomcat::Tomcat(NodeType nodeType) : Aircraft(true, TextureId::AircraftSpriteSheet, sf::IntRect(240, 298, 52, 12)),
	m_nodeType(Aircraft::getNodeType() | (unsigned int)nodeType)
{
	setScale(1.0f, 1.0f);
}

void Tomcat::update(float deltaTime)
{
	Aircraft::update(deltaTime);
	handleAnimation(deltaTime);
}

void Tomcat::collision(const Entity* other)
{
	GameSprite::collision(other);

	if((other->getNodeType() & (unsigned int)NodeType::Enemy) > 0)
	{
		takeDamage(10);
	}
	else if((other->getNodeType() & (unsigned int)NodeType::Projectile) > 0)
	{
		const auto* projectile = static_cast<const Projectile*>(other);
		if(projectile == nullptr)
		{
			Debug::logError(std::logic_error("Entity set as Projectile type, but is not."));
			return;
		}

		if(projectile->getOwnerType() == NodeType::Enemy)
			takeDamage(20);
	}
}
