// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file Player.h
 * @brief Declaration of the Player class.
 *
 * This header defines the Player class, which handles player input, network events,
 * and command dispatching for an aircraft. It integrates key bindings, real-time input,
 * and network communication to control player actions.
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Network/TcpSocket.hpp>
#include "CommandQueue.h"
#include "Aircraft.h"
#include "World.h"
#include "KeyBinding.h"

/**
 * @class Player
 * @brief Manages input events, network communication, and action commands for an aircraft.
 *
 * The Player class processes both discrete events and real-time input,
 * dispatching corresponding commands to the game world and handling network
 * synchronization for player actions.
 */
class Player
{
 public:
	/**
	 * @enum MissionStatus
	 * @brief Represents the outcome of a player's mission.
	 */
	enum MissionStatus
	{
		None,    ///< Mission in progress or not set.
		Success, ///< Mission succeeded.
		Failure  ///< Mission failed.
	};

	/// Alias for the action type defined in LocalPlayerAction.
	typedef LocalPlayerAction::ActionType ActionType;

	/**
	 * @brief Constructs a Player.
	 * @param socket Pointer to the TCP socket used for network communication.
	 * @param identifier Unique identifier for the player's aircraft.
	 * @param binding Pointer to the key binding configuration; if null, the player is considered remote.
	 */
	Player(sf::TcpSocket* socket, sf::Int32 identifier, const KeyBinding* binding);

	/**
	 * @brief Processes a discrete SFML event.
	 * @param event The event to handle.
	 * @param commands The command queue to which resulting commands are pushed.
	 */
	void handleEvent(const sf::Event& event, CommandQueue& commands);

	/**
	 * @brief Processes realtime input for the player.
	 * @param commands The command queue to which realtime commands are pushed.
	 */
	void handleRealtimeInput(CommandQueue& commands);

	/**
	 * @brief Retrieves the player's mission status.
	 * @return The current mission status.
	 */
	MissionStatus getMissionStatus() { return m_missionStatus; }

	/**
	 * @brief Sets the player's mission status.
	 * @param missionStatus The new mission status.
	 */
	void setMissionStatus(MissionStatus missionStatus) { m_missionStatus = missionStatus; }

	/**
	 * @brief Determines if the player is local (i.e., has an associated key binding).
	 * @return True if the player is local; false if remote.
	 */
	bool isLocal() const;

	/**
	 * @brief Disables all realtime actions for the player.
	 *
	 * Sends network messages to turn off all realtime actions for this player.
	 */
	void disableAllRealtimeActions();

	/**
	 * @brief Handles realtime network input for remote players.
	 * @param commands The command queue to which network realtime commands are pushed.
	 */
	void handleRealtimeNetworkInput(CommandQueue& commands);

	/**
	 * @brief Processes a network event and pushes the corresponding command.
	 * @param action The action type received from the network.
	 * @param commands The command queue to which the command is pushed.
	 */
	void handleNetworkEvent(ActionType action, CommandQueue& commands);

	/**
	 * @brief Processes a change in realtime network action state.
	 * @param action The action type.
	 * @param actionEnabled True if the action is now enabled; false otherwise.
	 */
	void handleNetworkRealtimeChange(ActionType action, bool actionEnabled);

 private:
	/**
	 * @brief Determines if a given action type is a realtime action.
	 * @param actionType The action type to check.
	 * @return True if the action type is considered realtime; false otherwise.
	 */
	static bool isRealtimeAction(ActionType actionType);

 private:
	const KeyBinding* m_keyBinding;                  ///< Pointer to the player's key binding configuration.
	std::map<ActionType, Command> m_actionBinding;     ///< Maps action types to corresponding commands.

	static std::vector<ActionType> m_realTimeActionTypes; ///< List of all realtime action types.

	MissionStatus m_missionStatus;                   ///< Current mission status of the player.
	int m_identifier;                                ///< Unique identifier for the player's aircraft.
	sf::TcpSocket* m_socket;                         ///< Pointer to the TCP socket for network communication.
	std::map<ActionType, bool> m_actionProxies;        ///< Stores the state of realtime actions for networked players.
};

#endif //PLAYER_H_
