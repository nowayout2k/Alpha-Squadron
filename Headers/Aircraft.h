// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include "GameSprite.h"
#include "DataTables.h"
#include "GameText.h"
#include "Projectile.h"
#include "Animation.h"

#include <vector>

/**
 * @file Aircraft.h
 * @brief Declaration of the Aircraft class.
 *
 * This header declares the Aircraft class, which represents an aircraft entity in the game.
 * It provides interfaces for movement, firing, missile launching, health management,
 * AI behavior, and rendering (including explosion animations).
 */

// Constants for damage animation timing and spawn/despawn distances.
#define MAX_FIRE_RATE 3
#define MAX_MISSILE_COUNT 3
#define MAX_SPREAD_LEVEL 3

/**
 * @class Aircraft
 * @brief Represents an aircraft in the game.
 *
 * The Aircraft class extends GameSprite to encapsulate functionalities such as:
 * - Managing fire rate, missile count, and bullet spread.
 * - Handling health and damage animations.
 * - Executing AI-driven movement and position updates.
 * - Firing projectiles and launching missiles.
 */
class Aircraft : public GameSprite
{
 public:
	/**
	 * @brief Constructs an Aircraft.
	 * @param nodeType The node type flag for the aircraft.
	 * @param aircraftType The specific type of aircraft.
	 * @param position The initial position of the aircraft.
	 * @param scale The scale factor for the aircraft sprite.
	 */
	explicit Aircraft(NodeType nodeType, AircraftType aircraftType, sf::Vector2f position, sf::Vector2f scale);

	/// @brief Default destructor.
	~Aircraft() override = default;

	/**
	 * @brief Retrieves the composite node type for the aircraft.
	 * @return The node type flags combined with Aircraft-specific flags.
	 */
	unsigned int getNodeType() const override { return GameSprite::getNodeType() | static_cast<unsigned int>(NodeType::Aircraft) | static_cast<unsigned int>(m_nodeType); }

	/**
	 * @brief Loads resources (textures, animations) for the aircraft.
	 */
	void loadResources() override;

	/**
	 * @brief Renders the aircraft or its explosion animation if it is destroyed.
	 * @param target The render target to draw onto.
	 * @param states The current render states.
	 */
	void render(sf::RenderTarget&, sf::RenderStates) const override;

	/**
	 * @brief Adjusts the aircraft's fire rate level.
	 * @param increment The value to increase the fire rate level by.
	 */
	virtual void changeFireRate(int increment) { m_fireRateLevel = std::min(m_fireRateLevel + increment, MAX_FIRE_RATE); }

	/**
	 * @brief Adjusts the aircraft's missile count.
	 * @param increment The value to increase the missile count by.
	 */
	virtual void changeMissileCount(int increment) { m_missileCount = std::min(m_missileCount + increment, MAX_MISSILE_COUNT); }

	/**
	 * @brief Adjusts the aircraft's bullet spread level.
	 * @param increment The value to increase the spread level by.
	 */
	virtual void changeFireSpread(int increment) { m_spreadLevel = std::min(m_spreadLevel + increment, MAX_SPREAD_LEVEL); }

	/**
	 * @brief Adjusts the aircraft's health.
	 * @param increment The amount to change the health by (can be negative).
	 */
	virtual void changeHealth(float increment);

	/**
	 * @brief Returns the type of the aircraft.
	 * @return The AircraftType of this aircraft.
	 */
	AircraftType getAircraftType() { return m_aircraftType; }

	/**
	 * @brief Retrieves the current health of the aircraft.
	 * @return The health value.
	 */
	float getHealth() const { return m_health; }

	/**
	 * @brief Retrieves the maximum speed of the aircraft.
	 * @return The speed value.
	 */
	float getMaxSpeed() const { return m_speed; }

	/**
	 * @brief Returns the unique identifier of the aircraft.
	 * @return The identifier.
	 */
	int getIdentifier() const { return m_identifier; }

	/**
	 * @brief Returns the current missile count.
	 * @return The number of missiles available.
	 */
	int getMissileCount() { return m_missileCount; }

	/**
	 * @brief Sets the unique identifier for the aircraft.
	 * @param identifier The new identifier.
	 */
	void setIdentifier(int identifier) { m_identifier = identifier; }

	/**
	 * @brief Sets the health of the aircraft.
	 * @param health The new health value.
	 */
	void setHealth(float health) { m_health = health; }

	/**
	 * @brief Increases the aircraft's velocity by the specified vector.
	 * @param velocity The velocity vector to add.
	 */
	void accelerate(sf::Vector2f velocity) { setVelocity(getVelocity() + velocity); }

	/**
	 * @brief Increases the aircraft's velocity by the specified x and y values.
	 * @param x The x-component of the velocity.
	 * @param y The y-component of the velocity.
	 */
	void accelerate(float x, float y) { setVelocity(getVelocity() + sf::Vector2f(x, y)); }

	/**
	 * @brief Checks if the aircraft is currently exploding.
	 * @return True if the explosion animation is active and not complete.
	 */
	bool isExploding() const { return m_showExplosion && !m_explosion.isComplete(); }

	/**
	 * @brief Initiates the firing action for the aircraft.
	 */
	void fire();

	/**
	 * @brief Initiates a missile launch if available.
	 */
	void launchMissile();

	/**
	 * @brief Plays a local sound effect.
	 * @param commands The command queue to push the sound command.
	 * @param effect The sound effect identifier.
	 * @param volume The volume at which to play the sound.
	 */
	void playLocalSound(CommandQueue& commands, SoundFxId effect, float volume);

 protected:
	/**
	 * @brief Handles the damage animation based on time elapsed.
	 * @param deltaTime The time elapsed since the last update.
	 */
	virtual void handleDamageAnimation(sf::Time deltaTime);

	/**
	 * @brief Updates the aircraft state every frame.
	 * @param dt The time elapsed since the last update.
	 * @param commands The command queue to issue game commands.
	 */
	void update(sf::Time dt, CommandQueue& commands) override;

 private:
	/**
	 * @brief Creates a projectile (bullet or missile) and attaches it to the world node.
	 * @param node The world node to attach the projectile.
	 * @param projectileType The type of projectile to create.
	 * @param xOffset Horizontal offset for the projectile's spawn position.
	 * @param yOffset Vertical offset for the projectile's spawn position.
	 */
	void createProjectile(WorldNode& node, ProjectileType projectileType, float xOffset, float yOffset);

	/**
	 * @brief Updates the aircraft's position based on AI logic.
	 * @param deltaTime The time elapsed since the last update.
	 */
	void updateAiPosition(sf::Time deltaTime);

	/**
	 * @brief Moves the aircraft towards its starting position during spawn.
	 * @param deltaTime The time elapsed since the last update.
	 */
	void moveTowardsStart(sf::Time deltaTime);

	/**
	 * @brief Updates the aircraft's velocity for exiting the screen.
	 */
	void exitPhase();

	/**
	 * @brief Updates the aircraft's position by following predefined AI routines.
	 * @param deltaTime The time elapsed since the last update.
	 */
	void followAiRoutines(sf::Time deltaTime);

	/**
	 * @brief Checks and triggers projectile launch commands based on firing states and cooldowns.
	 * @param dt The time elapsed since the last update.
	 * @param commands The command queue for issuing projectile launch commands.
	 */
	void checkProjectileLaunch(sf::Time dt, CommandQueue& commands);

	/**
	 * @brief Creates bullet projectiles based on the current bullet spread level.
	 * @param node The world node to attach the bullets.
	 */
	void createBullets(WorldNode& node);

	/**
	 * @brief Updates the aircraft's roll animation based on vertical velocity.
	 */
	void updateRollAnimation();

	/**
	 * @brief Calculates the velocity vector for a given direction.
	 * @param direction The direction for which to calculate the velocity.
	 * @return The calculated velocity vector.
	 */
	sf::Vector2f calculateDirectionalVelocity(Direction direction) const;

	/**
	 * @brief Determines if the aircraft is allied with the player.
	 * @return True if allied; false otherwise.
	 */
	bool isAllied() const;

	int m_identifier;                   ///< Unique identifier for the aircraft.
	int m_fireRateLevel{};              ///< Current fire rate level.
	int m_spreadLevel{};                ///< Current bullet spread level.
	int m_missileCount{};               ///< Remaining missile count.
	int m_routineIndex;                 ///< Current index in the AI routine list.
	float m_health{};                   ///< Current health points.
	float m_speed{};                    ///< Maximum speed of the aircraft.
	float m_timeSinceDamage;            ///< Time elapsed since the last damage was taken.
	float m_fireCooldownRemaining;      ///< Remaining cooldown time before the next allowed fire.
	float m_routineDistanceTravelled;   ///< Distance travelled while following the current AI routine.
	float m_spawnDistanceTravelled;     ///< Distance travelled since spawning.
	float m_despawnDistance{};          ///< Distance at which the aircraft despawns.
	bool m_isLaunchingMissile;          ///< Flag indicating a missile launch is in progress.
	bool m_isFiring;                    ///< Flag indicating the aircraft is firing.
	bool m_isDamageAnimationActive;     ///< Flag indicating that the damage animation is active.
	bool m_isExiting;                   ///< Flag indicating the aircraft is in the process of exiting.
	bool m_showExplosion;               ///< Flag to show the explosion animation.
	Command m_fireCommand;              ///< Command to fire bullets.
	Command m_missileCommand;           ///< Command to launch a missile.
	Animation m_explosion;              ///< Explosion animation for the aircraft.
	sf::Vector2f m_spawnPos;            ///< Initial spawn position.
	Direction m_enterDirection{};       ///< Direction from which the aircraft enters.
	Direction m_exitDirection{};        ///< Direction for the aircraft's exit.
	AircraftType m_aircraftType;        ///< Specific type of the aircraft.
	NodeType m_nodeType;                ///< Node type for this aircraft.
	std::vector<AiRoutine> m_aiRoutines; ///< AI movement routines for the aircraft.
};

#endif // AIRCRAFT_H_
