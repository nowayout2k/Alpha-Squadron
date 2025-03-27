// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file WorldNode.h
 * @brief Declaration of the WorldNode class.
 *
 * The WorldNode class is the base class for all nodes in the world scene graph.
 * It provides functionality for hierarchical transformations, drawing, collision detection,
 * resource loading, command handling, and update propagation through its children.
 */

#ifndef WORLDNODE_H_
#define WORLDNODE_H_

#include <iostream>
#include <set>
#include <SFML/Graphics.hpp>
#include "NodeType.h"

namespace Engine
{

	class CommandQueue;
	class Command;

	class WorldNode : public sf::Transformable, public sf::Drawable
	{
	 public:
		/// Smart pointer type for managing WorldNode objects.
		typedef std::unique_ptr<WorldNode> SmartNode;
		/// A pair of WorldNode pointers used in collision detection.
		typedef std::pair<WorldNode*, WorldNode*> Pair;

		// Disable copy constructor and assignment operator.
		WorldNode(const WorldNode&) = delete;
		WorldNode& operator=(const WorldNode& other) = delete;

		/**
		 * @brief Constructs a WorldNode.
		 *
		 * By default, the node is created as non-collidable.
		 */
		explicit WorldNode() : WorldNode(false)
		{
		}

		/**
		 * @brief Constructs a WorldNode with a specified collidability.
		 * @param isCollidable Indicates whether the node should be collidable.
		 */
		explicit WorldNode(bool isCollidable)
			: m_isActive(true),
			  m_parent(nullptr),
			  m_isDestroyed(false),
			  m_isMarkedForRemoval(false),
			  m_isCollidable(isCollidable)
		{
		}

		/**
		 * @brief Attaches a child node to this node.
		 * @param node The smart pointer to the child node.
		 */
		void attachNode(SmartNode node);

		/**
		 * @brief Processes a command on this node and its children.
		 * @param command The command to process.
		 * @param deltaTime The elapsed time since the last update.
		 */
		void onCommand(const Command& command, sf::Time deltaTime);

		/**
		 * @brief Detaches a child node from this node.
		 * @param node The node to detach.
		 * @return A smart pointer to the detached node.
		 */
		SmartNode detachNode(const WorldNode& node);

		/// Sets the node's active status.
		void setActive(bool isActive)
		{
			m_isActive = isActive;
		}
		/// Returns whether the node is active.
		bool isActive() const
		{
			return m_isActive;
		};

		/**
		 * @brief Recursively renders this node and its children.
		 * @param renderTarget The target to draw on.
		 * @param states The current render states.
		 */
		virtual void renderState(sf::RenderTarget& renderTarget, sf::RenderStates states) const;

		/**
		 * @brief Retrieves the node's world position.
		 * @return The world position of this node.
		 */
		sf::Vector2f getWorldPosition() const;

		/**
		 * @brief Retrieves the bounding rectangle of the node.
		 * @return A FloatRect representing the node's bounds.
		 */
		virtual sf::FloatRect getBoundingRect() const;

		/**
		 * @brief Recursively updates the node and its children.
		 * @param deltaTime The elapsed time since the last update.
		 * @param commands The command queue for dispatching actions.
		 */
		virtual void updateHierarchy(sf::Time deltaTime, CommandQueue& commands);

		/**
		 * @brief Recursively loads resources for this node and its children.
		 */
		virtual void loadHierarchyResources();

		/**
		 * @brief Retrieves the composite node type.
		 * @return The node type as an unsigned int.
		 */
		virtual unsigned int getNodeType() const
		{
			return static_cast<unsigned int>(AlphaSquadron::NodeType::WorldNode);
		}

		/**
		 * @brief Checks collision between two nodes.
		 * @param lhs The first node.
		 * @param rhs The second node.
		 * @return True if both nodes are collidable and their bounding rectangles intersect.
		 */
		bool isColliding(const WorldNode& lhs, const WorldNode& rhs);

		/**
		 * @brief Checks for collisions between this node and a given node.
		 * @param node The node to check against.
		 * @param collisionPairs Set to store detected collision pairs.
		 */
		void checkNodeCollision(WorldNode& node, std::set<Pair>& collisionPairs);

		/**
		 * @brief Checks for collisions within the scene graph.
		 * @param sceneGraph The root of the scene graph.
		 * @param collisionPairs Set to store detected collision pairs.
		 */
		void checkWorldCollision(WorldNode& sceneGraph, std::set<Pair>& collisionPairs);

		/// Removes destroyed child nodes from the scene graph.
		void removeDestroyed();

		/// Marks this node as destroyed.
		virtual void destroy()
		{
			m_isDestroyed = true;
		}
		/// Checks if the node is destroyed.
		bool isDestroyed() const
		{
			return m_isDestroyed;
		}
		/// Checks if the node is marked for removal.
		bool isMarkedForRemoval() const
		{
			return m_isMarkedForRemoval;
		}
		/// Marks the node for removal.
		void markForRemoval()
		{
			m_isMarkedForRemoval = true;
		}
		/// Returns whether the node is collidable.
		bool isCollidable() const
		{
			return m_isCollidable;
		}
		/// Sets the node's collidability.
		void setIsCollidable(bool isCollidable)
		{
			m_isCollidable = isCollidable;
		}

	 protected:
		/**
		 * @brief Computes the world transform of this node by combining transforms up the hierarchy.
		 * @return The world transform.
		 */
		sf::Transform getWorldTransform() const;

		/**
		 * @brief Pure virtual function for rendering the node.
		 * @param renderTarget The target to draw on.
		 * @param states The current render states.
		 */
		virtual void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const = 0;

		/**
		 * @brief Pure virtual function for loading the node's resources.
		 */
		virtual void loadResources() = 0;

		/**
		 * @brief Pure virtual function for updating the node.
		 * @param deltaTime The elapsed time since the last update.
		 * @param commands The command queue for dispatching actions.
		 */
		virtual void update(sf::Time deltaTime, CommandQueue& commands) = 0;

	 private:
		/**
		 * @brief Draws the node by invoking renderState().
		 * @param target The render target.
		 * @param states The current render states.
		 */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

		bool m_isActive;                  ///< Indicates whether the node is active.
		bool m_isCollidable;              ///< Indicates whether the node can participate in collisions.
		std::vector<SmartNode> m_children;///< Child nodes attached to this node.
		WorldNode* m_parent;              ///< Pointer to the parent node.
		bool m_isDestroyed;               ///< Flag indicating if the node is destroyed.
		bool m_isMarkedForRemoval;        ///< Flag indicating if the node is marked for removal.
	};
}

#endif //WORLDNODE_H_
