//
// Created by Johnnie on 3/12/2025.
//

#ifndef ALPHA_SQUADRON_SOURCE_NETWORKNODE_H_
#define ALPHA_SQUADRON_SOURCE_NETWORKNODE_H_

#include <queue>
#include <SFML/System/Vector2.hpp>
#include "WorldNode.h"
#include "../Headers/NetworkProtocol.h"
#include "EmptyWorldNode.h"

class NetworkNode : public EmptyWorldNode
{
 public:
	NetworkNode();

	void notifyGameAction(GameActions::Type type, sf::Vector2f position);
	bool pollGameAction(GameActions::Action& out);
	unsigned int getNodeType() const override { return EmptyWorldNode::getNodeType() | static_cast<unsigned int>(NodeType::Network); }

 private:
	std::queue<GameActions::Action>	m_pendingActions;
};

#endif //ALPHA_SQUADRON_SOURCE_NETWORKNODE_H_
