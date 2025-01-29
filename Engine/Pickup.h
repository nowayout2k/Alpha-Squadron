//
// Created by Johnnie Otis on 1/29/25.
//

#ifndef PICKUP_H_
#define PICKUP_H_

#include "Entity.h"
#include "../Game/Aircraft.h"

class Pickup : public GameSprite
{
 public:
	enum Type
	{
		HealthRefill,
		MissileRefill,
		FireSpread,
		FireRate,
		Count
	};
 public:
	explicit Pickup(Type type);
	virtual unsigned int getCategory() const;
	virtual sf::FloatRect getBoundingRect() const;
	void apply(Aircraft& player) const;
 protected:
	virtual void drawCurrent(sf::RenderTarget& target,
		sf::RenderStates states) const;
 private:
	Type m_type;
	sf::Sprite m_sprite;
};

#endif //PICKUP_H_
