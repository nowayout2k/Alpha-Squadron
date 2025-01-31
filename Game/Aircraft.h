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

#define MAX_FIRE_RATE 3
#define MAX_MISSILE_COUNT 3
#define MAX_SPREAD_LEVEL 3

class Aircraft : public GameSprite
{
 public:
	explicit Aircraft(bool hasCollision, sf::Vector2f scale, sf::Vector2f position);
	~Aircraft() override = default;

	float getHealth() const { return m_health; }
	void setHealth(float health) { m_health = health; }

	void accelerate(sf::Vector2f velocity) { setVelocity(getVelocity() + velocity); }
	void accelerate(float x, float y) { setVelocity(getVelocity() + sf::Vector2f(x, y)); }

	float getMaxSpeed() const { return m_speed; }
	virtual AircraftType getAircraftType() = 0;

	void loadResources() override;
	void fire();
	void launchMissile();
	virtual void changeFireRate(int increment) { m_fireRateLevel = std::min(m_fireRateLevel + increment, MAX_FIRE_RATE); }
	virtual void changeMissileCount(int increment) { m_missileCount = std::min(m_missileCount + increment, MAX_MISSILE_COUNT); }
	virtual void changeFireSpread(int increment) { m_spreadLevel = std::min(m_spreadLevel + increment, MAX_SPREAD_LEVEL); }
	virtual void changeHealth(float increment);
 protected:
	virtual void handleAnimation(float deltaTime);
	void handleDamageAnimation(float deltaTime);
	void update(float deltaTime, CommandQueue& commands) override;
	unsigned int getNodeType() const override { return GameSprite::getNodeType() | (unsigned int)NodeType::Aircraft; }

 private:
	void createProjectile(WorldNode& node, ProjectileType projectileType, float xOffset, float yOffset);
	void updateHealthDisplay();
	void updatePosition(float deltaTime);
	void moveTowardsStart(float deltaTime);
	void exitPhase();
	void followAiRoutines(float deltaTime);
	sf::Vector2f calculateDirectionalVelocity(Direction direction) const;
	bool isAllied() const;
	void checkProjectileLaunch(float dt, CommandQueue& commands);
	void createBullets(WorldNode& node);

	float m_health{};
	float m_speed{};
	float m_timeSinceDamage;
	float m_fireCooldownRemaining;
	float m_routineDistanceTravelled;
	float m_spawnDistanceTravelled;
	bool m_isFiring;
	Command m_fireCommand;
	Command m_missileCommand;
	int m_fireRateLevel{};
	bool m_isLaunchingMissile;
	int m_spreadLevel{};
	int m_missileCount{};

	bool m_isDamageAnimationActive;
	bool m_isExiting;

	int m_routineIndex;
	float m_despawnDistance{};

	GameText* m_healthDisplay;
	std::vector<AiRoutine> m_aiRoutines;

	sf::Vector2f m_spawnPos;
	Direction m_enterDirection{};
	Direction m_exitDirection{};
};

#endif //AIRCRAFT_H_
