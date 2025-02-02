// Copyright (c) 2025 No Way Out LLC All rights reserved.


#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "NodeType.h"
#include "WorldNode.h"
#include "Debug.h"

class Entity : public WorldNode
{
 public:
	virtual ~Entity() = default;
	virtual void loadResources() override = 0;
	bool hasCollision() const { return m_hasCollision; }
	void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
	void setVelocity(float x, float y) { m_velocity.x = x; m_velocity.y = y; }
	sf::Vector2f getVelocity() const { return m_velocity; }
	void update(float deltaTime, CommandQueue& commands) override { if(isActive()) {move(m_velocity * deltaTime);} }
	virtual unsigned int getNodeType() const override { return WorldNode::getNodeType() | (unsigned int)NodeType::Entity; }
protected:
	Entity(bool hasCollision) : m_velocity(sf::Vector2f(0,0)), m_hasCollision(hasCollision) {}
	Entity() : m_velocity(sf::Vector2f(0,0)), m_hasCollision(false) {}

 private:
	bool m_hasCollision;
	sf::Vector2f m_velocity;
};

#endif //ENTITY_H_
