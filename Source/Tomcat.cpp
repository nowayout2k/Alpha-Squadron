//
// Created by Johnnie Otis on 6/2/24.
//

#include "../Headers/Tomcat.h"

#define DAMAGE_FLASH_TIME 4.0f
#define DAMAGE_INVINCIBILITY_TIME .3f
#define FIRE_COOLDOWN_TIME 0.2f

Tomcat::Tomcat(bool hasCollision, sf::Vector2f position, NodeType nodeType, sf::Vector2f scale) : Aircraft(hasCollision, scale, position),
	m_nodeType(Aircraft::getNodeType() | (unsigned int)nodeType)
{
}

void Tomcat::update(float deltaTime, CommandQueue& commands)
{
	Aircraft::update(deltaTime, commands);
	handleAnimation(deltaTime);
}
