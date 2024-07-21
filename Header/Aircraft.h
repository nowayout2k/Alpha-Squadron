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
	int getHealth() { return m_health; }
	virtual WorldNode::SmartNode fireBullet(sf::Vector2f velocity);
 protected:
	virtual void handleAnimation(float deltaTime);
	void handleDamageAnimation(float deltaTime);
	virtual void takeDamage(int health);
	virtual void update(float deltaTime) override;
	void setHealth(int health) { m_health = health; }
 private:
	float m_timeSinceDamage;
	bool m_isDamageAnimationActive;
	int m_health;
	float m_fireCooldownRemaining;
};

#endif //AIRCRAFT_H_
