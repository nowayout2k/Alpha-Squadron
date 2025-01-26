//
// Created by Johnnie Otis on 7/9/24.
//

#ifndef EMPTYWORLDNODE_H_
#define EMPTYWORLDNODE_H_

#include "WorldNode.h"

class EmptyWorldNode : public WorldNode
{
 public:
	EmptyWorldNode() : type(NodeType::None) {};
	explicit EmptyWorldNode(NodeType type): type(type){};
	unsigned int getNodeType() const override { return WorldNode::getNodeType() | (unsigned int)type; }
	void update(float deltaTime, CommandQueue& commands) override {  }
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override {  }
	void loadResources() override {  };
 private:
	NodeType type;
};
#endif //EMPTYWORLDNODE_H_
