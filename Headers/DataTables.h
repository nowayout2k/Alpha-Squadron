// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef DATATABLES_H_
#define DATATABLES_H_

// Standard library and SFML includes.
#include <SFML/Graphics/Rect.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>

// Local includes using quotes.
#include "TextureId.h"
#include "AircraftType.h"
#include "AiRoutine.h"
#include "Direction.h"
#include "PickupType.h"
#include "ProjectileType.h"
#include "Particle.h"

class Aircraft; // Forward declaration

/**
 * @file DataTables.h
 * @brief Declarations for game data structures and a function to load them from a JSON file.
 *
 * This file defines the data structures used to configure various game elements,
 * such as aircraft, pickups, projectiles, and particles. It also declares the LoadData
 * function which loads these configurations from a file.
 */

/**
 * @brief Data for configuring an aircraft.
 */
struct AircraftData
{
	AircraftType Type;               ///< The type of the aircraft.
	float Health;                    ///< Health points of the aircraft.
	float Speed;                     ///< Maximum speed of the aircraft.
	float DespawnDistance;           ///< Distance at which the aircraft despawns.
	Direction EnterDirection;        ///< Entry direction for AI.
	Direction ExitDirection;         ///< Exit direction for AI.
	TextureId TextureId;             ///< Identifier for the aircraft's texture.
	sf::IntRect TextureLoadArea;     ///< Region of the texture to load.
	sf::IntRect SpriteTextureRegion; ///< Region of the texture used for the sprite.
	std::vector<AiRoutine> AiRoutines; ///< Collection of AI routines.
};

/**
 * @brief Data for configuring a pickup.
 */
struct PickupData
{
	PickupType Type;                        ///< The type of the pickup.
	float Value;                            ///< The value (e.g., health or fire rate bonus).
	TextureId TextureId;                    ///< Identifier for the pickup's texture.
	sf::IntRect TextureLoadArea;            ///< Region of the texture to load.
	std::function<void(Aircraft&)> Action;    ///< Action to perform when the pickup is collected.
};

/**
 * @brief Data for configuring a projectile.
 */
struct ProjectileData
{
	ProjectileType Type{};          ///< The type of the projectile.
	TextureId TextureId{};          ///< Identifier for the projectile's texture.
	sf::IntRect TextureLoadArea{};  ///< Region of the texture to load.
	float MaxSpeed{};               ///< Maximum speed of the projectile.
};

/**
 * @brief Data for configuring a particle effect.
 */
struct ParticleData
{
	Particle::Type Type{};  ///< The type of the particle.
	sf::Color Color;        ///< Color of the particle.
	sf::Time Lifetime;      ///< Lifetime of the particle.
};

/**
 * @brief Container for all game data.
 */
struct GameData
{
	std::unordered_map<AircraftType, AircraftData> AircraftData;       ///< Aircraft configuration data.
	std::unordered_map<PickupType, PickupData> PickupData;             ///< Pickup configuration data.
	std::unordered_map<ProjectileType, ProjectileData> ProjectileData; ///< Projectile configuration data.
	std::unordered_map<Particle::Type, ParticleData> ParticleData;     ///< Particle configuration data.
};

/**
 * @brief Loads game data from a JSON file.
 *
 * @param filename The path to the JSON file.
 * @return A GameData structure containing the loaded configurations.
 */
GameData LoadData(const std::string& filename);

#endif // DATATABLES_H_
