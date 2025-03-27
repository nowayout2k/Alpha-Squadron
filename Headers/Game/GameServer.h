// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON_HEADERS_GAMESERVER_H_
#define ALPHA_SQUADRON_HEADERS_GAMESERVER_H_

#include <SFML/System/Vector2.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <map>
#include <memory>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <string>
#include <vector>

namespace AlphaSquadron
{
	/**
	 * @file GameServer.h
	 * @brief Declaration of the GameServer class.
	 *
	 * The GameServer class manages network communications for a multiplayer game.
	 * It handles incoming connections, packet processing, client state updates, and game events.
	 * It also spawns enemies and notifies connected players of game events.
	 */
	class GameServer
	{
	 public:
		/**
		 * @brief Constructs a GameServer.
		 * @param battlefieldSize The size of the battlefield.
		 */
		explicit GameServer(sf::Vector2f battlefieldSize);

		/**
		 * @brief Destructor.
		 */
		~GameServer();

		/**
		 * @brief Notifies all clients that a player has spawned.
		 * @param aircraftIdentifier The identifier of the spawned aircraft.
		 */
		void notifyPlayerSpawn(sf::Int32 aircraftIdentifier);

		/**
		 * @brief Notifies all clients of a player's realtime action change.
		 * @param aircraftIdentifier The identifier of the aircraft.
		 * @param action The action identifier.
		 * @param actionEnabled Whether the action is enabled.
		 */
		void notifyPlayerRealtimeChange(sf::Int32 aircraftIdentifier, sf::Int32 action, bool actionEnabled);

		/**
		 * @brief Notifies all clients of a player event.
		 * @param aircraftIdentifier The identifier of the aircraft.
		 * @param action The action identifier.
		 */
		void notifyPlayerEvent(sf::Int32 aircraftIdentifier, sf::Int32 action);

	 private:
		/**
		 * @brief Structure representing a remote peer (client).
		 */
		struct RemotePeer
		{
			/**
			 * @brief Constructs a RemotePeer.
			 *
			 * Initializes the TCP socket in non-blocking mode.
			 */
			RemotePeer();

			sf::TcpSocket Socket;                     ///< TCP socket for communication.
			sf::Time LastPacketTime;                  ///< Time when the last packet was received.
			std::vector<sf::Int32> AircraftIdentifiers; ///< Identifiers of aircraft associated with this peer.
			bool Ready;                               ///< Flag indicating whether the peer is ready.
			bool TimedOut;                            ///< Flag indicating whether the peer has timed out.
		};

		/**
		 * @brief Structure containing information about an aircraft.
		 */
		struct AircraftInfo
		{
			sf::Vector2f Position;                    ///< Position of the aircraft.
			sf::Int32 Hp;                             ///< Health points of the aircraft.
			sf::Int32 MissileAmmo;                    ///< Missile ammunition count.
			std::map<sf::Int32, bool> RealtimeActions; ///< Map of realtime actions and their states.
		};

		/// Unique pointer type for a remote peer.
		typedef std::unique_ptr<RemotePeer> PeerPtr;

	 private:
		/**
		 * @brief Sets the listening state of the server.
		 * @param enable True to enable listening; false to disable.
		 */
		void setListening(bool enable);

		/**
		 * @brief The main execution thread function.
		 */
		void executionThread();

		/**
		 * @brief Executes periodic server updates.
		 */
		void tick();

		/**
		 * @brief Returns the current elapsed time.
		 * @return The current time.
		 */
		sf::Time now() const;

		/**
		 * @brief Handles incoming packets from clients.
		 */
		void handleIncomingPackets();

		/**
		 * @brief Processes a single incoming packet.
		 * @param packet The packet to process.
		 * @param receivingPeer The peer that sent the packet.
		 * @param detectedTimeout Reference flag set to true if a timeout is detected.
		 */
		void handleIncomingPacket(sf::Packet& packet, RemotePeer& receivingPeer, bool& detectedTimeout);

		/**
		 * @brief Handles new incoming client connections.
		 */
		void handleIncomingConnections();

		/**
		 * @brief Handles disconnections of timed-out clients.
		 */
		void handleDisconnections();

		/**
		 * @brief Sends the current world state to a newly connected client.
		 * @param socket The client's TCP socket.
		 */
		void informWorldState(sf::TcpSocket& socket);

		/**
		 * @brief Broadcasts a message to all connected clients.
		 * @param message The message to broadcast.
		 */
		void broadcastMessage(const std::string& message);

		/**
		 * @brief Sends a packet to all connected clients.
		 * @param packet The packet to send.
		 */
		void sendToAll(sf::Packet& packet);

		/**
		 * @brief Updates the state of all clients.
		 */
		void updateClientState();

	 private:
		sf::Thread m_thread;                     ///< Thread for server execution.
		sf::Clock m_clock;                       ///< Clock for measuring elapsed time.
		sf::TcpListener m_listenerSocket;        ///< TCP listener for accepting connections.
		bool m_listeningState;                   ///< Current listening state.
		sf::Time m_clientTimeoutTime;            ///< Duration after which a client times out.

		std::size_t m_maxConnectedPlayers;       ///< Maximum number of connected players.
		std::size_t m_connectedPlayers;          ///< Current number of connected players.

		float m_worldWidth;                      ///< Width of the game world.
		sf::FloatRect m_battleFieldRect;           ///< Battlefield rectangle.
		float m_battleFieldScrollSpeed;            ///< Scroll speed of the battlefield.

		std::size_t m_aircraftCount;             ///< Count of aircraft currently in the game.
		std::map<sf::Int32, AircraftInfo> m_aircraftInfo; ///< Mapping from aircraft identifiers to their info.

		std::vector<PeerPtr> m_peers;            ///< List of connected peers.
		sf::Int32 m_aircraftIdentifierCounter;   ///< Counter for unique aircraft identifiers.
		bool m_waitingThreadEnd;                 ///< Flag indicating if the execution thread should end.

		sf::Time m_lastSpawnTime;                ///< Time when the last enemy was spawned.
		sf::Time m_timeForNextSpawn;             ///< Time interval until the next enemy spawn.
	};
}

#endif // ALPHA_SQUADRON_HEADERS_GAMESERVER_H_
