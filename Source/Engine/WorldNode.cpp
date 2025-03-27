// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file WorldNode.cpp
 * @brief Implementation of the WorldNode class.
 *
 * This source file implements the WorldNode class methods for hierarchical rendering,
 * updating, collision detection, resource loading, and command handling.
 */

#include "../../Headers/Engine/WorldNode.h"
#include "../../Headers/Engine/Debug.h"
#include "../../Headers/Engine/Command.h"

namespace Engine
{
	void WorldNode::renderState(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// Combine this node's transform with the current render states.
		states.transform *= getTransform();
		// Render the current node.
		render(target, states);
		// Recursively render all child nodes.
		for (const SmartNode& child : m_children)
		{
			child->renderState(target, states);
		}
	}

	sf::Transform WorldNode::getWorldTransform() const
	{
		sf::Transform transform = sf::Transform::Identity;
		// Multiply transforms up the hierarchy to compute the world transform.
		for (const WorldNode* node = this; node != nullptr; node = node->m_parent)
			transform = node->getTransform() * transform;
		return transform;
	}

	sf::Vector2f WorldNode::getWorldPosition() const
	{
		// Get the world position by applying the world transform to the origin.
		return getWorldTransform() * sf::Vector2f();
	}

	void WorldNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// Final drawing function called by SFML.
		renderState(target, states);
	}

	void WorldNode::updateHierarchy(sf::Time deltaTime, CommandQueue& commands)
	{
		// If the node is not active, do not update it or its children.
		if (!isActive())
			return;
		// Update this node.
		update(deltaTime, commands);
		// Recursively update all children.
		for (const SmartNode& child : m_children)
		{
			if (child == nullptr)
			{
				Engine::Debug::logWarning("Child node is null!");
				continue;
			}
			child->updateHierarchy(deltaTime, commands);
		}
	}

	void WorldNode::attachNode(WorldNode::SmartNode child)
	{
		// Set the child's parent pointer and add it to the children list.
		child->m_parent = this;
		m_children.push_back(std::move(child));
	}

	WorldNode::SmartNode WorldNode::detachNode(const WorldNode& node)
	{
		// Find the node to detach among the children.
		auto found = std::find_if(m_children.begin(), m_children.end(),
			[&](SmartNode& p) -> bool
			{ return p.get() == &node; });
		if (found != m_children.end())
			Engine::Debug::logError("Child is not present so it cannot be detached.");
		SmartNode result = std::move(*found);
		result->m_parent = nullptr;
		m_children.erase(found);
		return result;
	}

	void WorldNode::checkNodeCollision(WorldNode& node, std::set<Pair>& collisionPairs)
	{
		// Check collision between this node and the provided node if they are not the same.
		if (this != &node && isColliding(*this, node) && !isDestroyed() && !node.isDestroyed())
			collisionPairs.insert(std::minmax(this, &node));
		// Recursively check collision for each child.
		for (SmartNode& child : m_children)
			child->checkNodeCollision(node, collisionPairs);
	}

	void WorldNode::checkWorldCollision(WorldNode& sceneGraph, std::set<Pair>& collisionPairs)
	{
		// Check collision between this node and the entire scene graph.
		checkNodeCollision(sceneGraph, collisionPairs);
		// Recursively check collisions for each child of the scene graph.
		for (SmartNode& child : sceneGraph.m_children)
			checkWorldCollision(*child, collisionPairs);
	}

	bool WorldNode::isColliding(const WorldNode& lhs, const WorldNode& rhs)
	{
		// Two nodes are colliding if they are both collidable and their bounding rectangles intersect.
		return lhs.m_isCollidable && rhs.m_isCollidable && lhs.getBoundingRect().intersects(rhs.getBoundingRect());
	}

	void WorldNode::removeDestroyed()
	{
		// Remove children that are marked for removal.
		auto destroyedBegin =
			std::remove_if(m_children.begin(), m_children.end(), std::mem_fn(&WorldNode::isMarkedForRemoval));
		m_children.erase(destroyedBegin, m_children.end());
		// Recursively call removeDestroyed on remaining children.
		std::for_each(m_children.begin(), m_children.end(), std::mem_fn(&WorldNode::removeDestroyed));
	}

	sf::FloatRect WorldNode::getBoundingRect() const
	{
		// Default bounding rectangle (can be overridden in derived classes).
		return sf::FloatRect();
	}

	void WorldNode::loadHierarchyResources()
	{
		// Load resources for this node.
		loadResources();
		// Recursively load resources for each child.
		for (const SmartNode& child : m_children)
		{
			child->loadHierarchyResources();
		}
	}

	void WorldNode::onCommand(const Command& command, sf::Time deltaTime)
	{
		// If this node's type matches the command's NodeType, execute the command action.
		if (command.NodeType & getNodeType())
		{
			command.Action(*this, deltaTime);
		}
		// Pass the command down to all children.
		for (auto& child : m_children)
			child->onCommand(command, deltaTime);
	}
}