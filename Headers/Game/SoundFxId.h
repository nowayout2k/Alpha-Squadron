// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file SoundFxId.h
 * @brief Declaration of the SoundFxId enumeration.
 *
 * This header defines the SoundFxId enumeration, which lists identifiers for various
 * sound effects used in the game. These identifiers are utilized to load and play the
 * corresponding sound effects in response to in-game events.
 */

#ifndef SOUNDFXID_H_
#define SOUNDFXID_H_

namespace AlphaSquadron
{
	/**
	 * @enum SoundFxId
	 * @brief Enumerates sound effect identifiers.
	 *
	 * This enumeration specifies the different sound effects available in the game,
	 * such as button clicks, explosions, and various other in-game sounds.
	 */
	enum class SoundFxId
	{
		ButtonClick,    ///< Sound effect for button clicks.
		Explosion,      ///< Sound effect for explosions.
		MenuClick,      ///< Sound effect for menu clicks.
		BulletLaunch,   ///< Sound effect for bullet launches.
		MissileLaunch,  ///< Sound effect for missile launches.
		CollectPickup,  ///< Sound effect for collecting pickups.
		DamageWarning1, ///< First damage warning sound effect.
		DamageWarning2, ///< Second damage warning sound effect.
		TakeDamage      ///< Sound effect for taking damage.
	};
}
#endif //SOUNDFXID_H_
