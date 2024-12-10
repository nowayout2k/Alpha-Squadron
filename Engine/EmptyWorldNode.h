//
// Created by Johnnie Otis on 7/9/24.
//

#ifndef EMPTYWORLDNODE_H_
#define EMPTYWORLDNODE_H_

#include "WorldNode.h"

class EmptyWorldNode : public WorldNode
{
 public:
	void update(float deltaTime, CommandQueue& commands) override {}
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override {}
	void loadResources() override {};
};
#endif //EMPTYWORLDNODE_H_
