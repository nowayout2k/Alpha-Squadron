// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file ProjectileType.h
 * @brief Declaration of the ProjectileType enumeration.
 *
 * This header defines the ProjectileType enumeration, which specifies the
 * different types of projectiles available in the game. It is used to determine
 * projectile behavior, appearance, and damage characteristics.
 */

#ifndef PROJECTILETYPE_H_
#define PROJECTILETYPE_H_

/**
 * @enum ProjectileType
 * @brief Enumerates the types of projectiles in the game.
 *
 * This enumeration allows the game to differentiate between various projectile
 * behaviors such as those for bullets and missiles.
 */
enum ProjectileType
{
	Bullet,    ///< Represents a bullet projectile.
	Missile,   ///< Represents a missile projectile.
	TypeCount  ///< Total count of projectile types.
};

#endif //PROJECTILETYPE_H_
