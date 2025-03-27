// Copyright (c) 2025 No Way Out LLC All rights reserved.
/**
 * @file NetworkNode.cpp
 * @brief Implements the NetworkNode class functionalities.
 *
 * This source file provides the implementation of the NetworkNode class declared
 * in NetworkNode.h, handling the queuing and retrieval of network-triggered game actions.
 */

#include "../Headers/NetworkNode.h"

NetworkNode::NetworkNode()
	: EmptyWorldNode(), m_pendingActions()
{
	// Constructor initializes the base EmptyWorldNode and sets up an empty queue.
}

void NetworkNode::notifyGameAction(GameActions::Type type, sf::Vector2f position)
{
	// Add a new game action to the pending actions queue.
	m_pendingActions.emplace(type, position);
}

bool NetworkNode::pollGameAction(GameActions::Action& out)
{
	// If there are no pending actions, return false.
	if (m_pendingActions.empty())
	{
		return false;
	}
	else
	{
		// Retrieve and remove the front action from the queue.
		out = m_pendingActions.front();
		m_pendingActions.pop();
		return true;
	}
}
