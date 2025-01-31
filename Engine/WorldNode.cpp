//
// Created by Johnnie Otis on 6/30/24.
//
#include "WorldNode.h"
#include "Debug.h"
#include "Command.h"

void WorldNode::renderState(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	render(target, states);
	for (const SmartNode& child : m_children)
	{
		child->renderState(target, states);
	}
}

sf::Transform WorldNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const WorldNode* node = this; node != nullptr; node = node->m_parent)
		transform = node->getTransform() * transform;

	return transform;
}

sf::Vector2f WorldNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

void WorldNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	draw(target, states);
}

void WorldNode::updateHierarchy(float deltaTime, CommandQueue& commands)
{
	if(!isActive())
		return;

	update(deltaTime, commands);
	for (const SmartNode& child : m_children)
	{
		if(child == nullptr)
		{
			Debug::logWarning("Child node is null!");
			continue;
		}
		child->updateHierarchy(deltaTime, commands);
	}
}

void WorldNode::attachNode(WorldNode::SmartNode child)
{
	child->m_parent = this;
	m_children.push_back(std::move(child));
}

WorldNode::SmartNode WorldNode::detachNode(const WorldNode& node)
{
	auto found = std::find_if(m_children.begin(), m_children.end(),
		[&] (SmartNode& p) -> bool { return p.get() == &node; });
	if(found != m_children.end())
		Debug::logError("Child is not present so it cannot be detached.");
	SmartNode result = std::move(*found);
	result->m_parent = nullptr;
	m_children.erase(found);
	return result;
}

void WorldNode::checkNodeCollision(WorldNode& node, std::set<Pair>& collisionPairs)
{
	if (this != &node && isColliding(*this, node) && !isDestroyed() && !node.isDestroyed())
		collisionPairs.insert(std::minmax(this, &node));
	for(SmartNode& child : m_children)
		child->checkNodeCollision(node, collisionPairs);
}

void WorldNode::checkWorldCollision(WorldNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	checkNodeCollision(sceneGraph, collisionPairs);
	for(SmartNode& child : sceneGraph.m_children)
		checkWorldCollision(*child, collisionPairs);
}

bool WorldNode::isColliding(const WorldNode& lhs, const WorldNode& rhs)
{
	return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

void WorldNode::removeDestroyed()
{
	auto destroyedBegin = std::remove_if(m_children.begin(), m_children.end(),
		std::mem_fn(&WorldNode::isMarkedForRemoval));
	m_children.erase(destroyedBegin, m_children.end());
	std::for_each(m_children.begin(), m_children.end(),
		std::mem_fn(&WorldNode::removeDestroyed));
}

sf::FloatRect WorldNode::getBoundingRect() const
{
	return sf::FloatRect();
}

void WorldNode::loadHierarchyResources()
{
	loadResources();
	for (const SmartNode& child : m_children)
	{
		child->loadHierarchyResources();
	}
}

void WorldNode::onCommand(const Command& command, float deltaTime)
{
	if (command.nodeType & getNodeType())
	{
		command.action(*this, deltaTime);
	}

	for(auto& child : m_children)
		child->onCommand(command, deltaTime);
}
