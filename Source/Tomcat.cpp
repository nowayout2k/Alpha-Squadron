// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Tomcat.h"

Tomcat::Tomcat(bool hasCollision, sf::Vector2f position, NodeType nodeType, sf::Vector2f scale) : Aircraft(hasCollision, scale, position),
	m_nodeType(Aircraft::getNodeType() | (unsigned int)nodeType)
{

}

void Tomcat::update(float deltaTime, CommandQueue& commands)
{
	Aircraft::update(deltaTime, commands);
	handleAnimation(deltaTime);
}
