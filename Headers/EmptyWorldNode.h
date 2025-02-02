// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef EMPTYWORLDNODE_H_
#define EMPTYWORLDNODE_H_

#include "WorldNode.h"

class EmptyWorldNode : public WorldNode
{
 public:
	EmptyWorldNode() : m_type(NodeType::None) {};
	explicit EmptyWorldNode(NodeType type): m_type(type){};
	unsigned int getNodeType() const override { return WorldNode::getNodeType() | (unsigned int)m_type; }
	void update(float deltaTime, CommandQueue& commands) override {  }
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override {  }
	void loadResources() override {  };
	sf::Rect<float> getGlobalBounds() const override { return sf::Rect<float>(); }
 private:
	NodeType m_type;
};
#endif //EMPTYWORLDNODE_H_
