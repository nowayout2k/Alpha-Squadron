//
// Created by Johnnie on 5/29/2024.
//

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

//TODO: Explore using a component based system
class Entity : public WorldNode
{
 public:
	virtual ~Entity() = default;
	virtual void loadResources() override = 0;
	virtual void collision(const Entity* other) = 0;
	virtual bool isColliding(const sf::Rect<float>& bounds) const = 0;
	virtual sf::Rect<float> getGlobalBounds() const = 0;
	bool hasCollision() const { return m_hasCollision; }
	bool isDestroyPending() { return m_isDestroyPending; }
	void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
	void setVelocity(float x, float y) { m_velocity.x = x; m_velocity.y = y; }
	sf::Vector2f getVelocity() const { return m_velocity; }
	void update(float deltaTime) override { if(isActive()) move(m_velocity * deltaTime); }
	virtual unsigned int getNodeType() const override { return WorldNode::getNodeType() | (unsigned int)NodeType::Entity; }
protected:
	Entity(bool hasCollision) : m_velocity(sf::Vector2f(0,0)), m_isDestroyPending(false), m_hasCollision(hasCollision) {}
	Entity() : m_velocity(sf::Vector2f(0,0)), m_isDestroyPending(false), m_hasCollision(false) {}
	void setCollision(bool hasCollision) { m_hasCollision = hasCollision; };
	virtual void destroy() { m_isDestroyPending = true; }
 private:
	bool m_isDestroyPending;
	bool m_hasCollision;
	sf::Vector2f m_velocity;
};

#endif //ENTITY_H_
