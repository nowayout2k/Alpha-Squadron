// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file NodeType.h
 * @brief Declaration of the NodeType enumeration.
 *
 * This header defines the NodeType enumeration used to categorize various
 * node types in the game engine. Each enumerator is defined as a bit flag,
 * enabling the combination of multiple node types.
 */

#ifndef NODETYPE_H_
#define NODETYPE_H_

#include <string>

namespace AlphaSquadron
{
	/**
	 * @enum NodeType
	 * @brief Enumerates different types of nodes in the game engine.
	 *
	 * The NodeType enumeration specifies the categories of nodes such as sprites,
	 * text, aircraft, players, and others. Each value is a bit flag to allow
	 * composite node types by bitwise operations.
	 */
	enum class NodeType
	{
		None = 0,                 ///< Represents no node type.
		WorldNode = 1 << 0,       ///< Node belonging to the game world.
		GameSprite = 1 << 1,      ///< Node representing a game sprite.
		Text = 1 << 2,            ///< Node for text elements.
		Aircraft = 1 << 3,        ///< Node representing an aircraft entity.
		Player = 1 << 4,          ///< Node representing a player entity.
		ParticleSystem = 1 << 5,  ///< Node for particle systems.
		Enemy = 1 << 6,           ///< Node for enemy entities.
		EnemyProjectile = 1 << 7, ///< Node for projectiles fired by enemies.
		AlliedProjectile = 1 << 8,///< Node for projectiles fired by allied entities.
		SpriteFrontLayer = 1 << 9,///< Node for sprites in the front rendering layer.
		Pickup = 1 << 10,         ///< Node representing a pickup item.
		UiCanvas = 1 << 11,       ///< Node for UI canvas elements.
		Sound = 1 << 12,          ///< Node for sound elements.
		Network = 1 << 13         ///< Node associated with network functionality.
	};
}
#endif //NODETYPE_H_
