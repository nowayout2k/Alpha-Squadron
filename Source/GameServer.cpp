// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include "../Headers/GameServer.h"
#include "../Headers/NetworkProtocol.h"
#include "../Headers/Utility.h"
#include "../Headers/Pickup.h"
#include "../Headers/Aircraft.h"
#include <SFML/Network/Packet.hpp>

namespace AlphaSquadron
{

	GameServer::RemotePeer::RemotePeer()
		: Ready(false), TimedOut(false)
	{
		Socket.setBlocking(false);
	}

	GameServer::GameServer(sf::Vector2f battlefieldSize)
		: m_thread(&GameServer::executionThread, this),
		  m_listeningState(false),
		  m_clientTimeoutTime(sf::seconds(3.f)),
		  m_maxConnectedPlayers(10),
		  m_connectedPlayers(0),
		  m_worldWidth(10000.f),
		  m_battleFieldRect(0, 0, battlefieldSize.x, battlefieldSize.y),
		  m_battleFieldScrollSpeed(500.f),
		  m_aircraftCount(0),
		  m_peers(1),
		  m_aircraftIdentifierCounter(1),
		  m_waitingThreadEnd(false),
		  m_lastSpawnTime(sf::Time::Zero),
		  m_timeForNextSpawn(sf::seconds(5.f))
	{
		m_listenerSocket.setBlocking(false);
		m_peers[0].reset(new RemotePeer());
		m_thread.launch();
	}

	GameServer::~GameServer()
	{
		m_waitingThreadEnd = true;
		m_thread.wait();
	}

	void GameServer::notifyPlayerRealtimeChange(sf::Int32 aircraftIdentifier, sf::Int32 action, bool actionEnabled)
	{
		for (std::size_t i = 0; i < m_connectedPlayers; ++i)
		{
			if (m_peers[i]->Ready)
			{
				sf::Packet packet;
				packet << static_cast<sf::Int32>(Engine::Server::PlayerRealtimeChange);
				packet << aircraftIdentifier;
				packet << action;
				packet << actionEnabled;
				m_peers[i]->Socket.send(packet);
			}
		}
	}

	void GameServer::notifyPlayerEvent(sf::Int32 aircraftIdentifier, sf::Int32 action)
	{
		for (std::size_t i = 0; i < m_connectedPlayers; ++i)
		{
			if (m_peers[i]->Ready)
			{
				sf::Packet packet;
				packet << static_cast<sf::Int32>(Engine::Server::PlayerEvent);
				packet << aircraftIdentifier;
				packet << action;
				m_peers[i]->Socket.send(packet);
			}
		}
	}

	void GameServer::notifyPlayerSpawn(sf::Int32 aircraftIdentifier)
	{
		for (std::size_t i = 0; i < m_connectedPlayers; ++i)
		{
			if (m_peers[i]->Ready)
			{
				sf::Packet packet;
				packet << static_cast<sf::Int32>(Engine::Server::PlayerConnect);
				packet << aircraftIdentifier
					   << m_aircraftInfo[aircraftIdentifier].Position.x
					   << m_aircraftInfo[aircraftIdentifier].Position.y;
				m_peers[i]->Socket.send(packet);
			}
		}
	}

	void GameServer::setListening(bool enable)
	{
		// Enable listening if not already active.
		if (enable)
		{
			if (!m_listeningState)
				m_listeningState = (m_listenerSocket.listen(Engine::ServerPort) == sf::TcpListener::Done);
		}
		else
		{
			m_listenerSocket.close();
			m_listeningState = false;
		}
	}

	void GameServer::executionThread()
	{
		setListening(true);

		sf::Time stepInterval = sf::seconds(1.f / 60.f);
		sf::Time stepTime = sf::Time::Zero;
		sf::Time tickInterval = sf::seconds(1.f / 20.f);
		sf::Time tickTime = sf::Time::Zero;
		sf::Clock stepClock, tickClock;

		while (!m_waitingThreadEnd)
		{
			handleIncomingPackets();
			handleIncomingConnections();

			stepTime += stepClock.getElapsedTime();
			stepClock.restart();

			tickTime += tickClock.getElapsedTime();
			tickClock.restart();

			// Fixed update step: update battlefield position.
			while (stepTime >= stepInterval)
			{
				m_battleFieldRect.left += m_battleFieldScrollSpeed * stepInterval.asSeconds();
				stepTime -= stepInterval;
			}

			// Fixed tick step: perform periodic server updates.
			while (tickTime >= tickInterval)
			{
				tick();
				tickTime -= tickInterval;
			}

			// Sleep briefly to reduce CPU usage.
			sf::sleep(sf::milliseconds(100));
		}
	}

	void GameServer::tick()
	{
		updateClientState();

		// Check for mission success: all aircraft have passed the world width.
		bool allAircraftsDone = !m_aircraftInfo.empty();
		for (auto& pair : m_aircraftInfo)
		{
			if (pair.second.Position.x < m_worldWidth)
				allAircraftsDone = false;
		}
		if (allAircraftsDone)
		{
			sf::Packet missionSuccessPacket;
			missionSuccessPacket << static_cast<sf::Int32>(Engine::Server::MissionSuccess);
			sendToAll(missionSuccessPacket);
		}

		// Remove aircraft with zero or negative health.
		for (auto itr = m_aircraftInfo.begin(); itr != m_aircraftInfo.end();)
		{
			if (itr->second.Hp <= 0)
				m_aircraftInfo.erase(itr++);
			else
				++itr;
		}

		// Check if it's time to spawn enemy aircraft.
		if (now() >= m_timeForNextSpawn + m_lastSpawnTime)
		{
			if (m_battleFieldRect.left < 9000.f)
			{
				std::size_t enemyCount = Engine::Utility::getRandomNumber(1, 2);
				float spawnCenter = Engine::Utility::getRandomNumber(-250.f, 250.f);

				float planeDistance = 0.f;
				float nextSpawnPosition = spawnCenter;

				if (enemyCount == 2)
				{
					planeDistance = Engine::Utility::getRandomNumber(150.f, 400.f);
					nextSpawnPosition = spawnCenter - planeDistance / 2.f;
				}

				// Broadcast enemy spawn orders to all clients.
				for (std::size_t i = 0; i < enemyCount; ++i)
				{
					sf::Packet packet;
					packet << static_cast<sf::Int32>(Engine::Server::SpawnEnemy);
					packet << static_cast<sf::Int32>(Engine::Utility::getRandomNumber(1u,
						static_cast<unsigned int>(AircraftType::AircraftTypeCount) - 1));
					packet << m_battleFieldRect.left + m_battleFieldRect.width + 100;
					packet << nextSpawnPosition;
					nextSpawnPosition += planeDistance / 2.f;
					sendToAll(packet);
				}

				m_lastSpawnTime = now();
				m_timeForNextSpawn = sf::milliseconds(Engine::Utility::getRandomNumber(2000, 8000));
			}
		}
	}

	sf::Time GameServer::now() const
	{
		return m_clock.getElapsedTime();
	}

	void GameServer::handleIncomingPackets()
	{
		bool detectedTimeout = false;

		for (PeerPtr& peer : m_peers)
		{
			if (peer->Ready)
			{
				sf::Packet packet;
				while (peer->Socket.receive(packet) == sf::Socket::Done)
				{
					handleIncomingPacket(packet, *peer, detectedTimeout);
					peer->LastPacketTime = now();
					packet.clear();
				}

				if (now() >= peer->LastPacketTime + m_clientTimeoutTime)
				{
					peer->TimedOut = true;
					detectedTimeout = true;
				}
			}
		}

		if (detectedTimeout)
			handleDisconnections();
	}

	void GameServer::handleIncomingPacket(sf::Packet& p, RemotePeer& receivingPeer, bool& detectedTimeout)
	{
		sf::Int32 packetType;
		p >> packetType;

		switch (packetType)
		{
		case Engine::Client::Quit:
		{
			receivingPeer.TimedOut = true;
			detectedTimeout = true;
		}
			break;

		case Engine::Client::PlayerEvent:
		{
			sf::Int32 aircraftIdentifier;
			sf::Int32 action;
			p >> aircraftIdentifier >> action;
			notifyPlayerEvent(aircraftIdentifier, action);
		}
			break;

		case Engine::Client::PlayerRealtimeChange:
		{
			sf::Int32 aircraftIdentifier;
			sf::Int32 action;
			bool actionEnabled;
			p >> aircraftIdentifier >> action >> actionEnabled;
			m_aircraftInfo[aircraftIdentifier].RealtimeActions[action] = actionEnabled;
			notifyPlayerRealtimeChange(aircraftIdentifier, action, actionEnabled);
		}
			break;

		case Engine::Client::RequestCoopPartner:
		{
			receivingPeer.AircraftIdentifiers.push_back(m_aircraftIdentifierCounter);
			m_aircraftInfo[m_aircraftIdentifierCounter].Position =
				sf::Vector2f(m_battleFieldRect.left + m_battleFieldRect.width / 2, m_battleFieldRect.height / 2);
			m_aircraftInfo[m_aircraftIdentifierCounter].Hp = 100;
			m_aircraftInfo[m_aircraftIdentifierCounter].MissileAmmo = 2;

			sf::Packet requestPacket;
			requestPacket << static_cast<sf::Int32>(Engine::Server::AcceptCoopPartner);
			requestPacket << m_aircraftIdentifierCounter;
			requestPacket << m_aircraftInfo[m_aircraftIdentifierCounter].Position.x;
			requestPacket << m_aircraftInfo[m_aircraftIdentifierCounter].Position.y;

			receivingPeer.Socket.send(requestPacket);
			m_aircraftCount++;

			for (PeerPtr& peer : m_peers)
			{
				if (peer.get() != &receivingPeer && peer->Ready)
				{
					sf::Packet notifyPacket;
					notifyPacket << static_cast<sf::Int32>(Engine::Server::PlayerConnect);
					notifyPacket << m_aircraftIdentifierCounter;
					notifyPacket << m_aircraftInfo[m_aircraftIdentifierCounter].Position.x;
					notifyPacket << m_aircraftInfo[m_aircraftIdentifierCounter].Position.y;
					peer->Socket.send(notifyPacket);
				}
			}
			m_aircraftIdentifierCounter++;
		}
			break;

		case Engine::Client::PositionUpdate:
		{
			sf::Int32 numAircrafts;
			p >> numAircrafts;
			for (sf::Int32 i = 0; i < numAircrafts; ++i)
			{
				sf::Int32 aircraftIdentifier;
				sf::Int32 aircraftHitpoints;
				sf::Int32 missileAmmo;
				sf::Vector2f aircraftPosition;
				p >> aircraftIdentifier >> aircraftPosition.x >> aircraftPosition.y >> aircraftHitpoints >> missileAmmo;
				m_aircraftInfo[aircraftIdentifier].Position = aircraftPosition;
				m_aircraftInfo[aircraftIdentifier].Hp = aircraftHitpoints;
				m_aircraftInfo[aircraftIdentifier].MissileAmmo = missileAmmo;
			}
		}
			break;

		case Engine::Client::GameEvent:
		{
			sf::Int32 action;
			float x;
			float y;
			p >> action;
			p >> x;
			p >> y;

			// If an enemy explodes and a random condition is met (only on the host peer), drop a pickup.
			if (action == Engine::GameActions::EnemyExplode && Engine::Utility::getRandomNumber(0, 3) == 0
				&& &receivingPeer == m_peers[0].get())
			{
				sf::Packet packet;
				packet << static_cast<sf::Int32>(Engine::Server::SpawnPickup);
				packet << static_cast<sf::Int32>(Engine::Utility::getRandomNumber(0u,
					static_cast<unsigned int>(PickupType::PickupCount)));
				packet << x;
				packet << y;
				sendToAll(packet);
			}
		}
			break;
		}
	}

	void GameServer::updateClientState()
	{
		sf::Packet updateClientStatePacket;
		updateClientStatePacket << static_cast<sf::Int32>(Engine::Server::UpdateClientState);
		updateClientStatePacket << static_cast<float>(m_battleFieldRect.left);
		updateClientStatePacket << static_cast<sf::Int32>(m_aircraftInfo.size());

		for (auto& aircraft : m_aircraftInfo)
			updateClientStatePacket << aircraft.first << aircraft.second.Position.x << aircraft.second.Position.y;

		sendToAll(updateClientStatePacket);
	}

	void GameServer::handleIncomingConnections()
	{
		if (!m_listeningState)
			return;

		if (m_listenerSocket.accept(m_peers[m_connectedPlayers]->Socket) == sf::TcpListener::Done)
		{
			m_aircraftInfo[m_aircraftIdentifierCounter].Position =
				sf::Vector2f(m_battleFieldRect.left, m_battleFieldRect.height / 2);
			m_aircraftInfo[m_aircraftIdentifierCounter].Hp = 100;
			m_aircraftInfo[m_aircraftIdentifierCounter].MissileAmmo = 2;

			sf::Packet packet;
			packet << static_cast<sf::Int32>(Engine::Server::SpawnSelf);
			packet << m_aircraftIdentifierCounter;
			packet << m_aircraftInfo[m_aircraftIdentifierCounter].Position.x;
			packet << m_aircraftInfo[m_aircraftIdentifierCounter].Position.y;

			m_peers[m_connectedPlayers]->AircraftIdentifiers.push_back(m_aircraftIdentifierCounter);

			broadcastMessage("New player!");
			informWorldState(m_peers[m_connectedPlayers]->Socket);
			notifyPlayerSpawn(m_aircraftIdentifierCounter++);

			m_peers[m_connectedPlayers]->Socket.send(packet);
			m_peers[m_connectedPlayers]->Ready = true;
			m_peers[m_connectedPlayers]->LastPacketTime = now(); // Prevent initial timeouts.
			m_aircraftCount++;
			m_connectedPlayers++;

			if (m_connectedPlayers >= m_maxConnectedPlayers)
				setListening(false);
			else // Add a new waiting peer.
				m_peers.push_back(std::make_unique<RemotePeer>());
		}
	}

	void GameServer::handleDisconnections()
	{
		for (auto itr = m_peers.begin(); itr != m_peers.end();)
		{
			if ((*itr)->TimedOut)
			{
				// Inform all peers of the disconnection and remove the aircraft.
				for (sf::Int32 identifier : (*itr)->AircraftIdentifiers)
				{
					sendToAll(sf::Packet() << static_cast<sf::Int32>(Engine::Server::PlayerDisconnect) << identifier);
					m_aircraftInfo.erase(identifier);
				}

				m_connectedPlayers--;
				m_aircraftCount -= (*itr)->AircraftIdentifiers.size();
				itr = m_peers.erase(itr);

				// If necessary, revert to listening state.
				if (m_connectedPlayers < m_maxConnectedPlayers)
				{
					m_peers.push_back(PeerPtr(new RemotePeer()));
					setListening(true);
				}

				broadcastMessage("An ally has disconnected.");
			}
			else
			{
				++itr;
			}
		}
	}

	void GameServer::informWorldState(sf::TcpSocket& socket)
	{
		sf::Packet packet;
		packet << static_cast<sf::Int32>(Engine::Server::InitialState);
		packet << m_worldWidth << m_battleFieldRect.left;
		packet << static_cast<sf::Int32>(m_aircraftCount);

		for (std::size_t i = 0; i < m_connectedPlayers; ++i)
		{
			if (m_peers[i]->Ready)
			{
				for (sf::Int32 identifier : m_peers[i]->AircraftIdentifiers)
				{
					packet << identifier
						   << m_aircraftInfo[identifier].Position.x
						   << m_aircraftInfo[identifier].Position.y
						   << m_aircraftInfo[identifier].Hp
						   << m_aircraftInfo[identifier].MissileAmmo;
				}
			}
		}

		socket.send(packet);
	}

	void GameServer::broadcastMessage(const std::string& message)
	{
		for (std::size_t i = 0; i < m_connectedPlayers; ++i)
		{
			if (m_peers[i]->Ready)
			{
				sf::Packet packet;
				packet << static_cast<sf::Int32>(Engine::Server::BroadcastMessage);
				packet << message;
				m_peers[i]->Socket.send(packet);
			}
		}
	}

	void GameServer::sendToAll(sf::Packet& packet)
	{
		for (PeerPtr& peer : m_peers)
		{
			if (peer->Ready)
				peer->Socket.send(packet);
		}
	}
}