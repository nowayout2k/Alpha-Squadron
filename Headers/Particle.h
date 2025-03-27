// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file Particle.h
 * @brief Declaration of the Particle structure.
 *
 * This header defines the Particle structure used in the particle system.
 * It contains properties for managing an individual particle's state,
 * including its position, color, and remaining lifetime.
 */

#ifndef ALPHA_SQUADRON_HEADERS_PARTICLE_H_
#define ALPHA_SQUADRON_HEADERS_PARTICLE_H_

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>

/**
 * @struct Particle
 * @brief Represents a single particle in the particle system.
 *
 * The Particle structure holds the properties for an individual particle,
 * such as its spatial position, visual color, and the time it remains active.
 */
struct Particle
{
	/**
	 * @enum Type
	 * @brief Enumerates possible particle types.
	 *
	 * The enumeration defines the types of particles, which can be used to
	 * differentiate behavior and appearance in the particle system.
	 */
	enum Type
	{
		None,             ///< No specific particle type.
		Propellant,       ///< Particle representing propellant effects.
		Smoke,            ///< Particle representing smoke effects.
		ParticleTypeCount ///< Total count of particle types.
	};

	sf::Vector2f Position; ///< The current position of the particle.
	sf::Color Color;       ///< The color of the particle.
	sf::Time Lifetime;     ///< The remaining lifetime of the particle.
};

#endif //ALPHA_SQUADRON_HEADERS_PARTICLE_H_
