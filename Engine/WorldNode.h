//
// Created by Johnnie Otis on 6/30/24.
//

#ifndef WORLDNODE_H_
#define WORLDNODE_H_
#include <iostream>
#include <SFML/Graphics.hpp>
#include "NodeType.h"

class Command;

class WorldNode : public sf::Transformable, public sf::Drawable
{
 public:
	typedef std::unique_ptr<WorldNode> SmartNode;
	WorldNode(const WorldNode&) = delete;
	WorldNode& operator=(const WorldNode& other) = delete;
	explicit WorldNode() : m_isActive(true), m_parent(nullptr) {}
	void attachNode(SmartNode node);
	SmartNode detachNode(const WorldNode& node);
	void setActive(bool isActive) { m_isActive = isActive; }
	bool isActive() const { return m_isActive; };
	virtual void updateState(float deltaTime);
	virtual void renderState(sf::RenderTarget& renderTarget, sf::RenderStates states) const;
	sf::Vector2f getWorldPosition() const;
	virtual void loadStateResources();
	virtual unsigned int getNodeType() const { return (unsigned int)NodeType::World; }
	void onCommand(const Command& command, float deltaTime);
 protected:
	sf::Transform getWorldTransform() const;
	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const = 0;
	virtual void loadResources() = 0;
 private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
	bool m_isActive;
	std::vector<SmartNode> m_children;
	WorldNode* m_parent;
};

#endif //WORLDNODE_H_
