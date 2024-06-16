//
// Created by Johnnie Otis on 6/9/24.
//

#ifndef ALPHA_SQUADRON_HEADER_CHARACTER_H_
#define ALPHA_SQUADRON_HEADER_CHARACTER_H_
#include "GameSprite.h"
#include "Entity.h"

class Character : public GameSprite
{
 public:
	explicit Character(const bool hasCollision, const TextureId textureType, const sf::IntRect textureRect = sf::IntRect());
	virtual ~Character() override = default;
	void update(float deltaTime) override = 0;
 protected:
	virtual void handleAnimation(float deltaTime);
	void handleDamageAnimation(float deltaTime);
	virtual void fireBullet(sf::Vector2f offset, sf::Vector2f velocity);
	virtual void takeDamage(int health);

	float m_timeSinceDamage;
	bool m_isDamageAnimationActive;
	int m_health;
	float m_fireCooldownRemaining;
};

#endif //ALPHA_SQUADRON_HEADER_CHARACTER_H_
