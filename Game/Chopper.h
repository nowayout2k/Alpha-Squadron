//
// Created by Johnnie Otis on 6/1/24.
//

#ifndef CHOPPER_H_
#define CHOPPER_H_


#include "../Engine/GameSprite.h"
#include "../Engine/Entity.h"
#include "Aircraft.h"

class Chopper : public Aircraft
{
public:
	explicit Chopper(bool hasCollision, sf::Vector2f position, NodeType nodeType = NodeType::None);
    void update(float deltaTime) override;
    void collision(const Entity* other) override;
	virtual unsigned int getNodeType() const override { return m_nodeType; }
 private:
	unsigned int m_nodeType;
};

#endif //CHOPPER_H_
