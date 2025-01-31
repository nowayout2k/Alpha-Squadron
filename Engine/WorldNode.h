//
// Created by Johnnie Otis on 6/30/24.
//

#ifndef WORLDNODE_H_
#define WORLDNODE_H_
#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>
#include "NodeType.h"

class CommandQueue;
class Command;

class WorldNode : public sf::Transformable, public sf::Drawable
{
 public:
	typedef std::unique_ptr<WorldNode> SmartNode;
	typedef std::pair<WorldNode*, WorldNode*> Pair;

	WorldNode(const WorldNode&) = delete;
	WorldNode& operator=(const WorldNode& other) = delete;
	explicit WorldNode() : m_isActive(true), m_parent(nullptr) {}
	void attachNode(SmartNode node);
	virtual sf::FloatRect getBoundingRect() const;
	void onCommand(const Command& command, float deltaTime);
	SmartNode detachNode(const WorldNode& node);
	void setActive(bool isActive) { m_isActive = isActive; }
	bool isActive() const { return m_isActive; };
	virtual void renderState(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
	sf::Vector2f getWorldPosition() const;
	virtual sf::Rect<float> getGlobalBounds() const = 0;
	virtual void updateHierarchy(float deltaTime, CommandQueue& commands);
	virtual void loadHierarchyResources();
	virtual unsigned int getNodeType() const { return (unsigned int)NodeType::WorldNode; }

	bool isColliding(const WorldNode& lhs, const WorldNode& rhs);
	void checkWorldCollision(WorldNode& sceneGraph, std::set<Pair>& collisionPairs);
	void checkNodeCollision(WorldNode& node, std::set<Pair>& collisionPairs);
	void removeDestroyed();
	virtual void destroy() { m_isDestroyed = true; }
	bool isDestroyed() { return m_isDestroyed; }
	bool isMarkedForRemoval() const { return m_isMarkedForRemoval; }
	void markForRemoval() { m_isMarkedForRemoval = true; }
 protected:
	sf::Transform getWorldTransform() const;
	virtual void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const = 0;
	virtual void loadResources() = 0;
	virtual void update(float deltaTime, CommandQueue& commands) = 0;

 private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
	bool m_isActive;
	std::vector<SmartNode> m_children;
	WorldNode* m_parent;
	bool m_isDestroyed;
	bool m_isMarkedForRemoval;
};

#endif //WORLDNODE_H_
