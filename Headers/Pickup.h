//
// Created by Johnnie Otis on 1/29/25.
//

#ifndef PICKUP_H_
#define PICKUP_H_

#include "Entity.h"
#include "Aircraft.h"
#include "PickupType.h"

class Pickup : public GameSprite
{

 public:
	explicit Pickup(PickupType type);
	unsigned int getNodeType() const override { return GameSprite::getNodeType() | (unsigned int)NodeType::Pickup; }
	void setPickupColor();
	void apply(Aircraft& player) const;
	void update(float deltaTime, CommandQueue& commands) override;
 protected:
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;

 private:
	PickupType m_type;
	sf::Sprite m_sprite;
};

#endif //PICKUP_H_
