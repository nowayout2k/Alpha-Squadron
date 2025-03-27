// Copyright (c) 2025 No Way Out LLC All rights reserved.
/**
 * @file MultiplayerGameState.h
 * @brief Declaration of the MultiplayerGameState class.
 *
 * This header declares the MultiplayerGameState class, which represents the state
 * for the multiplayer game. It handles network connections, game world updates,
 * player input, server communication, and in-game broadcast messaging.
 */

#ifndef ALPHA_SQUADRON_HEADERS_MULTIPLAYERGAMESTATE_H_
#define ALPHA_SQUADRON_HEADERS_MULTIPLAYERGAMESTATE_H_

#include "SFML/Network.hpp"
#include "StateStack.h"
#include "GameServer.h"

/**
 * @class MultiplayerGameState
 * @brief Manages the multiplayer game state and network communication.
 *
 * This class extends State to manage the multiplayer game. It handles:
 * - Establishing and maintaining a network connection.
 * - Processing incoming server packets and broadcasting messages.
 * - Updating the game world and synchronizing player states.
 * - Managing in-game UI elements such as connection messages and player invitations.
 */
class MultiplayerGameState : public State
{
 public:
	/**
	 * @brief Constructs a MultiplayerGameState.
	 * @param stack The state stack.
	 * @param context The context for resources and window.
	 * @param isHost Flag indicating if this instance is the host.
	 */
	MultiplayerGameState(StateStack& stack, Context context, bool isHost);

	/**
	 * @brief Renders the multiplayer game state.
	 */
	virtual void render();

	/**
	 * @brief Updates the multiplayer game state.
	 * @param dt Elapsed time since last update.
	 * @return True if the state should continue updating.
	 */
	bool update(sf::Time dt) override;

	/**
	 * @brief Handles SFML events.
	 * @param event The SFML event to process.
	 * @return True if the event was handled.
	 */
	bool handleEvent(const sf::Event& event) override;

 private:
	/**
	 * @brief Updates the broadcast message display based on elapsed time.
	 * @param elapsedTime Time elapsed since the last update.
	 */
	void updateBroadcastMessage(sf::Time elapsedTime);

	/**
	 * @brief Processes an incoming packet from the server.
	 * @param packetType The type of packet received.
	 * @param packet The packet data.
	 */
	void handlePacket(sf::Int32 packetType, sf::Packet& packet);

	/**
	 * @brief Activates the state.
	 */
	virtual void onActivate();

	/**
	 * @brief Cleans up resources when the state is destroyed.
	 */
	void onDestroy();

	/**
	 * @brief Disables all realtime actions for players.
	 */
	void disableAllRealtimeActions();

	// Type alias for a unique pointer to a Player.
	typedef std::unique_ptr<Player> PlayerPtr;

	// Member variables:
	World m_world;                              ///< The game world instance.
	sf::RenderWindow& m_window;                   ///< Reference to the render window.
	std::map<int, PlayerPtr> m_players;           ///< Map of players by their identifier.
	std::vector<sf::Int32> m_localPlayerIdentifiers; ///< List of local player identifiers.
	sf::TcpSocket m_socket;                       ///< TCP socket for network communication.
	bool m_connected;                             ///< Flag indicating if the connection is established.
	std::unique_ptr<GameServer> m_gameServer;     ///< Unique pointer to the game server (if hosting).
	sf::Clock m_tickClock;                        ///< Clock for timing regular updates.
	std::vector<std::string> m_broadcasts;        ///< List of broadcast messages.
	sf::Text m_broadcastText;                     ///< Text object for displaying broadcast messages.
	sf::Time m_broadcastElapsedTime;              ///< Elapsed time since the last broadcast update.

	sf::Text m_playerInvitationText;              ///< Text for inviting a second player.
	sf::Time m_playerInvitationTime;              ///< Timer for blinking the invitation text.

	sf::Text m_failedConnectionText;              ///< Text for displaying connection failure messages.
	sf::Clock m_failedConnectionClock;            ///< Clock for timing connection failure.

	bool m_activeState;                           ///< Flag indicating if the state is active.
	bool m_hasFocus;                              ///< Flag indicating if the window has focus.
	bool m_host;                                  ///< Flag indicating if this instance is the host.
	bool m_gameStarted;                           ///< Flag indicating if the game has started.
	sf::Time m_clientTimeout;                     ///< Timeout duration for client inactivity.
	sf::Time m_timeSinceLastPacket;               ///< Time elapsed since the last received packet.
};

#endif //ALPHA_SQUADRON_HEADERS_MULTIPLAYERGAMESTATE_H_
