// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef PARTICLETYPE_H_
#define PARTICLETYPE_H_

namespace AlphaSquadron
{
	/**
	 * @enum Type
	 * @brief Enumerates possible particle types.
	 *
	 * The enumeration defines the types of particles, which can be used to
	 * differentiate behavior and appearance in the particle system.
	 */
	enum ParticleType
	{
		None,             ///< No specific particle type.
		Propellant,       ///< Particle representing propellant effects.
		Smoke,            ///< Particle representing smoke effects.
		ParticleTypeCount ///< Total count of particle types.
	};
}
#endif //PARTICLETYPE_H_
