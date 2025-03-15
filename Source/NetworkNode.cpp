//
// Created by Johnnie on 3/12/2025.
//

#include "../Headers/NetworkNode.h"

NetworkNode::NetworkNode() : EmptyWorldNode(), m_pendingActions()
{

}

void NetworkNode::notifyGameAction(GameActions::Type type, sf::Vector2f position)
{
	m_pendingActions.emplace(type, position);
}

bool NetworkNode::pollGameAction(GameActions::Action& out)
{
	if (m_pendingActions.empty())
	{
		return false;
	}
	else
	{
		out = m_pendingActions.front();
		m_pendingActions.pop();
		return true;
	}
}