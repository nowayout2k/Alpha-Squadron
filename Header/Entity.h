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
#include "EntityType.h"

//TODO: Explore using a component based system
class Entity
{
 public:
	virtual ~Entity() = default;
	virtual void loadResources() = 0;
    virtual void update(float deltaTime)
	{
		if(!isActive())
			return;
	}
	virtual void render(sf::RenderWindow& renderWindow, sf::RenderStates states) = 0;
	virtual void collision(const Entity* other) = 0;
	virtual bool isColliding(const sf::Rect<float>& bounds) const = 0;
	virtual sf::Rect<float> getGlobalBounds() = 0;
	void setActive(bool isActive) { m_isActive = isActive; };
	bool hasCollision() const { return m_hasCollision; }
	bool isActive() const { return m_isActive; };
	bool isDestroyPending() { return m_isDestroyPending; }
	EntityType getEntityType() const { return m_entityType; };
protected:
	Entity(EntityType entityType, bool hasCollision) : m_entityType(entityType), m_isActive(true), m_isDestroyPending(false), m_hasCollision(hasCollision) {}
	Entity(EntityType entityType) : m_entityType(entityType), m_isActive(true), m_isDestroyPending(false), m_hasCollision(false) {}
	void setCollision(bool hasCollision) { m_hasCollision = hasCollision; };
	virtual void destroy()
	{
		m_isActive = false;
		m_isDestroyPending = true;
	}
 private:
	EntityType m_entityType;
	bool m_isActive;
	bool m_isDestroyPending;
	bool m_hasCollision;
};

#endif //ENTITY_H_
