//
// Created by Johnnie on 3/12/2025.
//

/**
 * @file NetworkProtocol.h
 * @brief Defines network protocol constants and enumerations for server-client communication.
 *
 * This header contains declarations of packet types for both the server and client,
 * as well as enumerations for player actions and game events. It standardizes the
 * communication protocol used in the networked game.
 */

#ifndef ALPHA_SQUADRON_SOURCE_NETWORKPROTOCOL_H_
#define ALPHA_SQUADRON_SOURCE_NETWORKPROTOCOL_H_

#include <SFML/System/Vector2.hpp>

/// Port number used for network communication between server and client.
const unsigned short ServerPort = 5394;

namespace Server
{
	/**
	 * @enum PacketType
	 * @brief Enumerates packet types originated by the server.
	 *
	 * The server sends packets of these types to communicate various events and states to the client.
	 * Some packet types include format specifications in their inline comments.
	 */
	enum PacketType
	{
		BroadcastMessage,	// format: [Int32:packetType] [string:message]
		SpawnSelf,			// format: [Int32:packetType]
		InitialState,
		PlayerEvent,
		PlayerRealtimeChange,
		PlayerConnect,
		PlayerDisconnect,
		AcceptCoopPartner,
		SpawnEnemy,
		SpawnPickup,
		UpdateClientState,
		MissionSuccess
	};
}

namespace Client
{
	/**
	 * @enum PacketType
	 * @brief Enumerates packet types originated by the client.
	 *
	 * The client uses these packet types to communicate player actions and requests to the server.
	 */
	enum PacketType
	{
		PlayerEvent,
		PlayerRealtimeChange,
		RequestCoopPartner,
		PositionUpdate,
		GameEvent,
		Quit
	};
}

namespace PlayerActions
{
	/**
	 * @enum Action
	 * @brief Enumerates possible realtime actions for a player.
	 *
	 * This enumeration defines the basic actions a player can perform,
	 * such as movement and combat actions.
	 */
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
		LaunchMissile,
		ActionCount
	};
}

namespace GameActions
{
	/**
	 * @enum Type
	 * @brief Enumerates game action types.
	 *
	 * Currently defines actions that are triggered by in-game events.
	 */
	enum Type
	{
		EnemyExplode,
	};

	/**
	 * @struct Action
	 * @brief Represents an action event in the game with its type and associated position.
	 *
	 * This structure is used to encapsulate game events, such as an enemy explosion,
	 * along with the position where the event occurred.
	 */
	struct Action
	{
		/**
		 * @brief Default constructor.
		 *
		 * Leaves the action type uninitialized.
		 */
		Action() : Type()
		{
			// leave uninitialized
		}

		/**
		 * @brief Constructs a game action with a specified type and position.
		 * @param type The type of game action.
		 * @param position The position where the action occurred.
		 */
		Action(Type type, sf::Vector2f position)
			: Type(type)
			, Position(position)
		{
		}

		Type Type;          ///< The type of game action.
		sf::Vector2f Position; ///< The position associated with the action.
	};
}

#endif //ALPHA_SQUADRON_SOURCE_NETWORKPROTOCOL_H_
