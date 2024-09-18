//
// Created by Johnnie Otis on 6/2/24.
//

#ifndef TOMCAT_H_
#define TOMCAT_H_


#include "../Engine/GameSprite.h"
#include "../Engine/Entity.h"
#include "Aircraft.h"


class Tomcat : public Aircraft
{
public:
    explicit Tomcat(NodeType nodeType = NodeType::None);
    void update(float deltaTime) override;
    void collision(const Entity* other) override;
	virtual unsigned int getNodeType() const override { return m_nodeType; }
 private:
    sf::Vector2f handleInput(float deltaTime);
	unsigned int m_nodeType;
};

#endif //TOMCAT_H_
