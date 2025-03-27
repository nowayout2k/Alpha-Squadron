// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file PooledSound.h
 * @brief Declaration of the PooledSound structure.
 *
 * This header defines the PooledSound structure, which is used for managing individual
 * sound objects within a sound pool. Each PooledSound contains an SFML sound object and
 * a flag to indicate its availability.
 */

#ifndef POOLEDSOUND_H_
#define POOLEDSOUND_H_

#include <SFML/Audio/Sound.hpp>

/**
 * @struct PooledSound
 * @brief Represents a sound in the pool along with its availability status.
 *
 * The PooledSound structure encapsulates an sf::Sound object and a boolean flag,
 * which is used to determine whether the sound is currently available for use.
 */
struct PooledSound
{
	sf::Sound Sound;       ///< The SFML sound object.
	bool IsAvailable = false; ///< Flag indicating whether the sound is available.
};

#endif //POOLEDSOUND_H_
