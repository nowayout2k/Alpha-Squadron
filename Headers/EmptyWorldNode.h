// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef EMPTYWORLDNODE_H_
#define EMPTYWORLDNODE_H_

#include "WorldNode.h"

/**
 * @file EmptyWorldNode.h
 * @brief Declaration of the EmptyWorldNode class.
 *
 * The EmptyWorldNode class provides a minimal implementation of WorldNode with no additional functionality.
 * It serves as a placeholder node in the scene graph.
 */
class EmptyWorldNode : public WorldNode
{
 public:
	/**
	 * @brief Constructs an EmptyWorldNode with no specific node type.
	 */
	EmptyWorldNode() : m_type(NodeType::None) {}

	/**
	 * @brief Constructs an EmptyWorldNode with the specified node type.
	 * @param type The node type to be combined with the base WorldNode type.
	 */
	explicit EmptyWorldNode(NodeType type) : m_type(type) {}

	/**
	 * @brief Retrieves the node type of this node.
	 * @return An unsigned integer representing the combined node type.
	 */
	unsigned int getNodeType() const override { return WorldNode::getNodeType() | static_cast<unsigned int>(m_type); }

	/**
	 * @brief Updates the node.
	 * @param deltaTime The time elapsed since the last update.
	 * @param commands The command queue for issuing commands.
	 */
	void update(sf::Time deltaTime, CommandQueue& commands) override { }

	/**
	 * @brief Renders the node.
	 * @param renderTarget The render target.
	 * @param states The current render states.
	 */
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override { }

	/**
	 * @brief Loads resources for the node.
	 */
	void loadResources() override { }

	/**
	 * @brief Retrieves the bounding rectangle of the node.
	 * @return An empty rectangle, as the node has no visible bounds.
	 */
	sf::Rect<float> getBoundingRect() const override { return {}; }

 private:
	NodeType m_type; ///< The specific node type for this empty node.
};

#endif // EMPTYWORLDNODE_H_
