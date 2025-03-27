// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file PickupType.h
 * @brief Declaration of the PickupType enumeration.
 *
 * This header defines the PickupType enumeration, which lists the different types
 * of pickups available in the game. These pickups are used to provide power-ups and
 * enhancements, such as health or missile refills and weapon upgrades.
 */

#ifndef PICKUP_TYPE_H_
#define PICKUP_TYPE_H_

/**
 * @enum PickupType
 * @brief Enumerates the different types of pickups in the game.
 *
 * This enumeration specifies the types of pickups that players can collect to gain
 * various benefits during gameplay.
 */
enum PickupType
{
	HealthRefill,   ///< Pickup that refills the player's health.
	MissileRefill,  ///< Pickup that refills the player's missile count.
	FireSpread,     ///< Pickup that increases the bullet spread.
	FireRate,       ///< Pickup that increases the firing rate.
	PickupCount     ///< Represents the total number of pickup types.
};

#endif //PICKUP_TYPE_H_
