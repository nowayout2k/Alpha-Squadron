//
// Created by Johnnie Otis on 6/9/24.
//

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include "../Engine/GameSprite.h"
#include "DataTables.h"
#include "../Engine/GameText.h"

class Aircraft : public GameSprite
{
 public:
	explicit Aircraft(const bool hasCollision, const TextureId textureType, const sf::IntRect textureRect = sf::IntRect());
	virtual ~Aircraft() override = default;
	int getHealth() { return m_health; }
	virtual WorldNode::SmartNode fireBullet(sf::Vector2f velocity);
	void accelerate(sf::Vector2f velocity) { setVelocity(getVelocity() + velocity); }
	void accelerate(float x, float y) { setVelocity(getVelocity() + sf::Vector2f(x,y)); }
	float getMaxSpeed() { return 800.f; }
 protected:
	virtual void handleAnimation(float deltaTime);
	void handleDamageAnimation(float deltaTime);
	virtual void takeDamage(int health);
	virtual void update(float deltaTime) override;
	void setHealth(int health) { m_health = health; }
	virtual unsigned int getNodeType() const override { return GameSprite::getNodeType() | (unsigned int)NodeType::Aircraft; }
 private:
	static std::vector<AircraftData> m_aircraftData;
	float m_timeSinceDamage;
	bool m_isDamageAnimationActive;
	int m_health;
	float m_fireCooldownRemaining;
	GameText* m_healthDisplay;
};

#endif //AIRCRAFT_H_
