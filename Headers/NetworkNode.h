// Copyright (c) 2025 No Way Out LLC All rights reserved.
/**
 * @file NetworkNode.h
 * @brief Declaration of the NetworkNode class.
 *
 * This header declares the NetworkNode class, which extends EmptyWorldNode
 * to provide functionality for queuing and polling game actions triggered by
 * network events.
 */

#ifndef ALPHA_SQUADRON_SOURCE_NETWORKNODE_H_
#define ALPHA_SQUADRON_SOURCE_NETWORKNODE_H_

#include <queue>
#include <SFML/System/Vector2.hpp>
#include "WorldNode.h"
#include "../Headers/NetworkProtocol.h"
#include "EmptyWorldNode.h"

namespace Engine
{
	/**
	 * @class NetworkNode
	 * @brief Represents a network-enabled world node.
	 *
	 * The NetworkNode class extends EmptyWorldNode to manage game actions that are
	 * received from network events. It allows actions to be notified and later polled
	 * by the game logic.
	 */
	class NetworkNode : public EmptyWorldNode
	{
	 public:
		/**
		 * @brief Constructs a NetworkNode.
		 *
		 * Initializes the base class and the internal queue for pending game actions.
		 */
		NetworkNode();

		/**
		 * @brief Notifies the node of a game action triggered by the network.
		 * @param type The type of game action.
		 * @param position The position associated with the game action.
		 */
		void notifyGameAction(GameActions::Type type, sf::Vector2f position);

		/**
		 * @brief Polls the next pending game action.
		 * @param out Reference to an Action object to be populated with the next action.
		 * @return True if an action was available and retrieved; false otherwise.
		 */
		bool pollGameAction(GameActions::Action& out);

		/**
		 * @brief Retrieves the composite node type for this network node.
		 * @return The node type flags combined with the Network flag.
		 */
		unsigned int getNodeType() const override
		{
			return EmptyWorldNode::getNodeType() | static_cast<unsigned int>(AlphaSquadron::NodeType::Network);
		}

	 private:
		std::queue<GameActions::Action>
			m_pendingActions; ///< Queue to store pending game actions received via the network.
	};
}
#endif //ALPHA_SQUADRON_SOURCE_NETWORKNODE_H_
