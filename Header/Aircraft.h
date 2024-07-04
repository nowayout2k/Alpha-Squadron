//
// Created by Johnnie Otis on 6/9/24.
//

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_
#include "../Header/GameSprite.h"

class Aircraft : public GameSprite
{
 public:
	explicit Aircraft(EntityType entityType, const bool hasCollision, const TextureId textureType, const sf::IntRect textureRect = sf::IntRect());
	virtual ~Aircraft() override = default;
 protected:
	virtual void handleAnimation(float deltaTime);
	void handleDamageAnimation(float deltaTime);
	virtual void fireBullet(sf::Vector2f position, sf::Vector2f velocity);
	virtual void takeDamage(int health);

	float m_timeSinceDamage;
	bool m_isDamageAnimationActive;
	int m_health;
	float m_fireCooldownRemaining;
};

#endif //AIRCRAFT_H_
