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
	explicit Aircraft(const bool hasCollision);
	explicit Aircraft(const bool hasCollision, sf::Vector2f scale);
	virtual ~Aircraft() override = default;
	int getHealth() { return m_health; }
	virtual void fireBullet(sf::Vector2f velocity);
	void accelerate(sf::Vector2f velocity) { setVelocity(getVelocity() + velocity); }
	void accelerate(float x, float y) { setVelocity(getVelocity() + sf::Vector2f(x,y)); }
	float getMaxSpeed() { return m_speed; }
	virtual AircraftType getAircraftType() = 0;
	virtual void loadResources() override;
 protected:
	virtual void handleAnimation(float deltaTime);
	void handleDamageAnimation(float deltaTime);
	virtual void takeDamage(int health);
	virtual void update(float deltaTime) override;
	void setHealth(int health) { m_health = health; }
	virtual unsigned int getNodeType() const override { return GameSprite::getNodeType() | (unsigned int)NodeType::Aircraft; }
	static std::vector<AircraftData> m_aircraftData;
 private:
	float m_timeSinceDamage;
	bool m_isDamageAnimationActive;
	int m_health;
	int m_speed;
	float m_travelledDistance;
	int m_directionIndex;
	float m_fireCooldownRemaining;
	GameText* m_healthDisplay;
	std::vector<Direction> m_directions;
};

#endif //AIRCRAFT_H_
