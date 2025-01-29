//
// Created by Johnnie Otis on 1/29/25.
//

#ifndef PICKUP_H_
#define PICKUP_H_

#include "Entity.h"
#include "../Game/Aircraft.h"
#include "../Game/PickupType.h"

class Pickup : public GameSprite
{

 public:
	explicit Pickup(PickupType type);
	virtual unsigned int getCategory() const;

	void apply(Aircraft& player) const;
 protected:
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;
 private:
	PickupType m_type;
	sf::Sprite m_sprite;
};

#endif //PICKUP_H_
