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
	explicit Aircraft(const bool hasCollision, sf::Vector2f scale, sf::Vector2f position);
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
	bool m_isMovingToStartPos;
	bool m_isExiting;
	int m_health;
	int m_speed;
	float m_routineDistanceTravelled;
	float m_spawnDistanceTravelled;
	int m_routineIndex;
	float m_fireCooldownRemaining;
	GameText* m_healthDisplay;
	std::vector<AiRoutine> m_aiRoutines;
	sf::Vector2f m_spawnPos;
	float m_despawnDistance;
	Direction m_enterDirection;
	Direction m_exitDirection;
};

#endif //AIRCRAFT_H_
