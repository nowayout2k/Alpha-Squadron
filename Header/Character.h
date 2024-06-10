//
// Created by Johnnie Otis on 6/9/24.
//

#ifndef ALPHA_SQUADRON_HEADER_CHARACTER_H_
#define ALPHA_SQUADRON_HEADER_CHARACTER_H_
#include "SpriteEntity.h"
#include "Entity.h"

class Character : public SpriteEntity
{
 public:
	explicit Character(const bool hasCollision, const std::string& pathToTexture, const sf::IntRect textureRect = sf::IntRect());
	virtual ~Character() override = default;
	void update(float deltaTime) override = 0;
	void collision(const Entity* other) override = 0;
 protected:
	virtual void handleAnimation(float deltaTime, sf::Vector2f offset);
	virtual void fireBullet(sf::Vector2f offset, sf::Vector2f velocity);
	virtual void takeDamage(int health);

	float m_timeSinceDamage;
	bool m_isBeingDamaged;
	int m_health;
	float m_fireCooldownRemaining;
};

#endif //ALPHA_SQUADRON_HEADER_CHARACTER_H_
