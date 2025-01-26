//
// Created by Johnnie Otis on 6/9/24.
//

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include "../Engine/GameSprite.h"
#include "DataTables.h"
#include "../Engine/GameText.h"
#include "../Engine/Projectile.h"
#include <vector>

class Aircraft : public GameSprite
{
 public:
	explicit Aircraft(bool hasCollision, sf::Vector2f scale, sf::Vector2f position);
	virtual ~Aircraft() override = default;

	int getHealth() const { return m_health; }
	void setHealth(int health) { m_health = health; }

	void accelerate(sf::Vector2f velocity) { setVelocity(getVelocity() + velocity); }
	void accelerate(float x, float y) { setVelocity(getVelocity() + sf::Vector2f(x, y)); }

	float getMaxSpeed() const { return m_speed; }
	virtual AircraftType getAircraftType() = 0;

	virtual void loadResources() override;
	void fire();
	void launchMissile();
 protected:
	virtual void handleAnimation(float deltaTime);
	void handleDamageAnimation(float deltaTime);
	virtual void takeDamage(int health);
	virtual void update(float deltaTime, CommandQueue& commands) override;
	virtual unsigned int getNodeType() const override { return GameSprite::getNodeType() | (unsigned int)NodeType::Aircraft; }

 private:
	void createProjectile(WorldNode& node, Projectile::Type projectileType, float xOffset, float yOffset);
	void updateHealthDisplay();
	void updatePosition(float deltaTime);
	void moveTowardsStart(float deltaTime);
	void exitPhase();
	void followAiRoutines(float deltaTime);
	sf::Vector2f calculateDirectionalVelocity(Direction direction) const;
	bool isAllied() const;
	void checkProjectileLaunch(float dt, CommandQueue& commands);
	void createBullets(WorldNode& node);
	static std::vector<AircraftData> m_aircraftData;

	int m_health{};
	int m_speed{};
	float m_timeSinceDamage;
	float m_fireCooldownRemaining;
	float m_routineDistanceTravelled;
	float m_spawnDistanceTravelled;
	bool m_isFiring;
	Command m_fireCommand;
	Command m_missileCommand;
	int m_fireRateLevel;
	bool m_isLaunchingMissile;
	int m_spreadLevel;

	bool m_isDamageAnimationActive;
	bool m_isExiting;

	int m_routineIndex;
	float m_despawnDistance{};

	GameText* m_healthDisplay;
	std::vector<AiRoutine> m_aiRoutines;

	sf::Vector2f m_spawnPos;
	Direction m_enterDirection;
	Direction m_exitDirection;
};

#endif //AIRCRAFT_H_
