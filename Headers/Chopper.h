//
// Created by Johnnie Otis on 6/1/24.
//

#ifndef CHOPPER_H_
#define CHOPPER_H_


#include "GameSprite.h"
#include "Entity.h"
#include "Aircraft.h"

class Chopper : public Aircraft
{
public:
	explicit Chopper(bool hasCollision, sf::Vector2f position, NodeType nodeType = NodeType::None, sf::Vector2f scale = sf::Vector2f());
    void update(float deltaTime, CommandQueue& commands) override;
	virtual unsigned int getNodeType() const override { return m_nodeType; }
	AircraftType getAircraftType() override { return AircraftType::Chopper; }
 private:
	unsigned int m_nodeType;
};

#endif //CHOPPER_H_
