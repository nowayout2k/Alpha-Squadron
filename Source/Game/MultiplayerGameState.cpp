// Copyright (c) 2025 No Way Out LLC All rights reserved.
/**
 * @file MultiplayerGameState.cpp
 * @brief Implements the MultiplayerGameState class functionalities.
 *
 * This source file provides the implementation details for the MultiplayerGameState class,
 * including network connection setup, game world updates, event handling, and packet processing.
 */

#include "../../Headers/Game/MultiplayerGameState.h"
#include "../../Headers/Engine/NetworkProtocol.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Network/IpAddress.hpp>

#include <fstream>
#include <memory>
namespace AlphaSquadron
{
	sf::IpAddress GetAddressFromFile()
	{
		{
			std::ifstream inputFile("ip.txt");
			std::string ipAddress;
			if (inputFile >> ipAddress)
				return ipAddress;
		}
		// If open/read failed, create new file with default local address.
		std::ofstream outputFile("ip.txt");
		std::string localAddress = "127.0.0.1";
		outputFile << localAddress;
		return localAddress;
	}

	MultiplayerGameState::MultiplayerGameState(Engine::StateStack& stack, Context context, bool isHost)
		: State(stack, context),
		  m_world(*context.Window, *context.Audio, true),
		  m_window(*context.Window),
		  m_connected(false),
		  m_gameServer(nullptr),
		  m_activeState(true),
		  m_hasFocus(true),
		  m_host(isHost),
		  m_gameStarted(false),
		  m_clientTimeout(sf::seconds(2.f)),
		  m_timeSinceLastPacket(sf::seconds(0.f))
	{
		// Setup broadcast text.
		m_broadcastText.setFont(ResourceManager::loadResource(Engine::FontId::Arnold));
		m_broadcastText.setPosition(1024.f / 2, 100.f);

		// Setup player invitation text.
		m_playerInvitationText.setFont(ResourceManager::loadResource(Engine::FontId::Arnold));
		m_playerInvitationText.setCharacterSize(20);
		m_playerInvitationText.setFillColor(sf::Color::White);
		m_playerInvitationText.setString("Press Enter to spawn player 2");
		m_playerInvitationText.setPosition(m_window.getSize().x / 2 - m_playerInvitationText.getLocalBounds().width / 2,
			m_window.getSize().y - m_playerInvitationText.getLocalBounds().height);

		// Setup failed connection text used for connection status messages.
		m_failedConnectionText.setFont(ResourceManager::loadResource(Engine::FontId::Arnold));
		m_failedConnectionText.setString("Attempting to connect...");
		m_failedConnectionText.setCharacterSize(35);
		m_failedConnectionText.setFillColor(sf::Color::White);
		Engine::Utility::centerOrigin(m_failedConnectionText);
		m_failedConnectionText.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);

		// Render an initial connection feedback frame.
		m_window.clear(sf::Color::Black);
		m_window.draw(m_failedConnectionText);
		m_window.display();
		m_failedConnectionText.setString("Could not connect to the remote server!");
		Engine::Utility::centerOrigin(m_failedConnectionText);

		// Determine IP address and initialize server or client connection.
		sf::IpAddress ip;
		if (isHost)
		{
			m_gameServer = std::make_unique<GameServer>(sf::Vector2f(m_window.getSize()));
			ip = "127.0.0.1";
		}
		else
		{
			ip = GetAddressFromFile();
		}

		// Attempt to connect to the server.
		if (m_socket.connect(ip, Engine::ServerPort, sf::seconds(5.f)) == sf::TcpSocket::Done)
			m_connected = true;
		else
			m_failedConnectionClock.restart();

		m_socket.setBlocking(false);

		// Play the game theme music.
		context.Audio->playMusic(MusicId::GameMusic, 12.f);
	}

	void MultiplayerGameState::render()
	{
		// If connected, render the game world and in-game UI elements.
		if (m_connected)
		{
			m_world.render();

			// Reset view for UI elements.
			m_window.setView(m_window.getDefaultView());

			// Draw broadcast text if available.
			if (!m_broadcasts.empty())
				m_window.draw(m_broadcastText);

			// Display player invitation text if only one player is present and the timer is active.
			if (m_localPlayerIdentifiers.size() < 2 && m_playerInvitationTime < sf::seconds(0.5f))
				m_window.draw(m_playerInvitationText);
		}
		else
		{
			// Render failed connection message.
			m_window.draw(m_failedConnectionText);
		}
	}

	void MultiplayerGameState::onActivate()
	{
		// Activate the multiplayer state.
		m_activeState = true;
	}

	void MultiplayerGameState::onDestroy()
	{
		// If not hosting and connected, inform the server that the client is disconnecting.
		if (!m_host && m_connected)
		{
			sf::Packet packet;
			packet << static_cast<sf::Int32>(Engine::Client::Quit);
			m_socket.send(packet);
		}
	}

	bool MultiplayerGameState::update(sf::Time dt)
	{
		// If connected, process network logic and update game world.
		if (m_connected)
		{
			m_world.update(dt);

			// Remove players whose aircraft are no longer in the game world.
			bool foundLocalPlane = false;
			for (auto itr = m_players.begin(); itr != m_players.end();)
			{
				// Check for presence of local player aircraft.
				if (std::find(m_localPlayerIdentifiers.begin(), m_localPlayerIdentifiers.end(), itr->first)
					!= m_localPlayerIdentifiers.end())
				{
					foundLocalPlane = true;
				}

				if (!m_world.getAircraft(itr->first))
				{
					itr = m_players.erase(itr);
					// If no players remain, trigger game over.
					if (m_players.empty())
						requestStackPush(StateId::GameOver);
				}
				else
				{
					++itr;
				}
			}

			// If no local player found after game start, end the game.
			if (!foundLocalPlane && m_gameStarted)
			{
				requestStackPush(StateId::GameOver);
			}

			// Process realtime input if state is active and window has focus.
			if (m_activeState && m_hasFocus)
			{
				Engine::CommandQueue& commands = m_world.getCommandQueue();
				for (auto& pair : m_players)
					pair.second->handleRealtimeInput(commands);
			}

			// Always process network input for players.
			Engine::CommandQueue& commands = m_world.getCommandQueue();
			for (auto& pair : m_players)
				pair.second->handleRealtimeNetworkInput(commands);

			// Process incoming server packets.
			{
				sf::Packet packet;
				if (m_socket.receive(packet) == sf::Socket::Done)
				{
					m_timeSinceLastPacket = sf::seconds(0.f);
					sf::Int32 packetType;
					packet >> packetType;
					handlePacket(packetType, packet);
				}
				else
				{
					// If no packet is received for too long, consider connection lost.
					if (m_timeSinceLastPacket > m_clientTimeout)
					{
						m_connected = false;
						m_failedConnectionText.setString("Lost connection to server");
						Engine::Utility::centerOrigin(m_failedConnectionText);
						m_failedConnectionClock.restart();
					}
				}
			}

			// Update broadcast messages.
			updateBroadcastMessage(dt);

			// Update the timer for the player invitation text blinking.
			m_playerInvitationTime += dt;
			if (m_playerInvitationTime > sf::seconds(1.f))
				m_playerInvitationTime = sf::Time::Zero;

			// Process game events and send them to the server.
			Engine::GameActions::Action gameAction;
			while (m_world.pollGameAction(gameAction))
			{
				sf::Packet packet;
				packet << static_cast<sf::Int32>(Engine::Client::GameEvent);
				packet << static_cast<sf::Int32>(gameAction.Type);
				packet << gameAction.Position.x;
				packet << gameAction.Position.y;
				m_socket.send(packet);
			}

			// Send regular position updates for local players.
			if (m_tickClock.getElapsedTime() > sf::seconds(1.f / 20.f))
			{
				sf::Packet positionUpdatePacket;
				positionUpdatePacket << static_cast<sf::Int32>(Engine::Client::PositionUpdate);
				positionUpdatePacket << static_cast<sf::Int32>(m_localPlayerIdentifiers.size());
				for (sf::Int32 identifier : m_localPlayerIdentifiers)
				{
					if (Aircraft* aircraft = m_world.getAircraft(identifier))
						positionUpdatePacket << identifier << aircraft->getPosition().x << aircraft->getPosition().y
											 << static_cast<sf::Int32>(aircraft->getHealth())
											 << static_cast<sf::Int32>(aircraft->getMissileCount());
				}
				m_socket.send(positionUpdatePacket);
				m_tickClock.restart();
			}

			m_timeSinceLastPacket += dt;
		}
			// If connection failed for more than 5 seconds, return to the menu.
		else if (m_failedConnectionClock.getElapsedTime() >= sf::seconds(5.f))
		{
			requestStateClear();
			requestStackPush(StateId::Menu);
		}

		return true;
	}

	void MultiplayerGameState::disableAllRealtimeActions()
	{
		// Disable realtime input for the state and all local players.
		m_activeState = false;
		for (sf::Int32 identifier : m_localPlayerIdentifiers)
			m_players[identifier]->disableAllRealtimeActions();
	}

	bool MultiplayerGameState::handleEvent(const sf::Event& event)
	{
		// Forward event to all players.
		Engine::CommandQueue& commands = m_world.getCommandQueue();
		for (auto& pair : m_players)
			pair.second->handleEvent(event, commands);

		// Process key events for co-op and pause.
		if (event.type == sf::Event::KeyPressed)
		{
			// If Enter is pressed and only one local player exists, request a co-op partner.
			if (event.key.code == sf::Keyboard::Return && m_localPlayerIdentifiers.size() == 1)
			{
				sf::Packet packet;
				packet << static_cast<sf::Int32>(Engine::Client::RequestCoopPartner);
				m_socket.send(packet);
			}
			// If Escape is pressed, disable realtime actions and push the pause state.
			else if (event.key.code == sf::Keyboard::P)
			{
				disableAllRealtimeActions();
				requestStackPush(StateId::NetworkPause);
			}
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			m_hasFocus = true;
		}
		else if (event.type == sf::Event::LostFocus)
		{
			m_hasFocus = false;
		}

		return true;
	}

	void MultiplayerGameState::updateBroadcastMessage(sf::Time elapsedTime)
	{
		// If there are no broadcast messages, do nothing.
		if (m_broadcasts.empty())
			return;

		// Update the elapsed time for the current broadcast message.
		m_broadcastElapsedTime += elapsedTime;
		if (m_broadcastElapsedTime > sf::seconds(2.5f))
		{
			// Remove the expired message.
			m_broadcasts.erase(m_broadcasts.begin());
			// If there is another message, display it immediately.
			if (!m_broadcasts.empty())
			{
				m_broadcastText.setString(m_broadcasts.front());
				Engine::Utility::centerOrigin(m_broadcastText);
				m_broadcastElapsedTime = sf::Time::Zero;
			}
		}
	}

	void MultiplayerGameState::handlePacket(sf::Int32 packetType, sf::Packet& packet)
	{
		// Process packets based on their type.
		switch (packetType)
		{
		case Engine::Server::BroadcastMessage:
		{
			std::string message;
			packet >> message;
			m_broadcasts.push_back(message);
			// If this is the first message, display it immediately.
			if (m_broadcasts.size() == 1)
			{
				m_broadcastText.setString(m_broadcasts.front());
				Engine::Utility::centerOrigin(m_broadcastText);
				m_broadcastElapsedTime = sf::Time::Zero;
			}
			break;
		}
		case Engine::Server::SpawnSelf:
		{
			sf::Int32 aircraftIdentifier;
			sf::Vector2f aircraftPosition;
			packet >> aircraftIdentifier >> aircraftPosition.x >> aircraftPosition.y;
			Aircraft* aircraft = m_world.addAircraft(aircraftIdentifier, true);
			aircraft->setPosition(aircraftPosition);
			m_players[aircraftIdentifier].reset(new Player(&m_socket, aircraftIdentifier, getContext().KeysPlayer1));
			m_localPlayerIdentifiers.push_back(aircraftIdentifier);
			m_gameStarted = true;
			break;
		}
		case Engine::Server::PlayerConnect:
		{
			sf::Int32 aircraftIdentifier;
			sf::Vector2f aircraftPosition;
			packet >> aircraftIdentifier >> aircraftPosition.x >> aircraftPosition.y;
			Aircraft* aircraft = m_world.addAircraft(aircraftIdentifier, false);
			aircraft->setPosition(aircraftPosition);
			m_players[aircraftIdentifier].reset(new Player(&m_socket, aircraftIdentifier, nullptr));
			break;
		}
		case Engine::Server::PlayerDisconnect:
		{
			sf::Int32 aircraftIdentifier;
			packet >> aircraftIdentifier;
			m_world.removeAircraft(aircraftIdentifier);
			m_players.erase(aircraftIdentifier);
			break;
		}
		case Engine::Server::InitialState:
		{
			sf::Int32 aircraftCount;
			float worldWidth, currentScroll;
			packet >> worldWidth >> currentScroll;
			m_world.setWorldWidth(worldWidth);
			m_world.setCurrentBattleFieldPosition(currentScroll);
			packet >> aircraftCount;
			for (sf::Int32 i = 0; i < aircraftCount; ++i)
			{
				sf::Int32 aircraftIdentifier;
				sf::Int32 hitpoints;
				sf::Int32 missileAmmo;
				sf::Vector2f aircraftPosition;
				packet >> aircraftIdentifier >> aircraftPosition.x >> aircraftPosition.y >> hitpoints >> missileAmmo;
				Aircraft* aircraft = m_world.addAircraft(aircraftIdentifier, true);
				aircraft->setPosition(aircraftPosition);
				aircraft->setHealth(hitpoints);
				aircraft->changeMissileCount(missileAmmo - aircraft->getMissileCount());
				m_players[aircraftIdentifier] = std::make_unique<Player>(&m_socket, aircraftIdentifier, nullptr);
			}
			break;
		}
		case Engine::Server::AcceptCoopPartner:
		{
			sf::Int32 aircraftIdentifier;
			packet >> aircraftIdentifier;
			m_world.addAircraft(aircraftIdentifier, true);
			m_players[aircraftIdentifier].reset(new Player(&m_socket, aircraftIdentifier, getContext().KeysPlayer2));
			m_localPlayerIdentifiers.push_back(aircraftIdentifier);
			break;
		}
		case Engine::Server::PlayerEvent:
		{
			sf::Int32 aircraftIdentifier;
			sf::Int32 action;
			packet >> aircraftIdentifier >> action;
			auto itr = m_players.find(aircraftIdentifier);
			if (itr != m_players.end())
				itr->second->handleNetworkEvent(static_cast<Engine::LocalPlayerAction::ActionType>(action),
					m_world.getCommandQueue());
			break;
		}
		case Engine::Server::PlayerRealtimeChange:
		{
			sf::Int32 aircraftIdentifier;
			sf::Int32 action;
			bool actionEnabled;
			packet >> aircraftIdentifier >> action >> actionEnabled;
			auto itr = m_players.find(aircraftIdentifier);
			if (itr != m_players.end())
				itr->second->handleNetworkRealtimeChange(static_cast<Engine::LocalPlayerAction::ActionType>(action),
					actionEnabled);
			break;
		}
		case Engine::Server::SpawnEnemy:
		{
			sf::Int32 type;
			float relativeY;
			float spawnDistance;
			packet >> type >> spawnDistance >> relativeY;
			m_world.addEnemy(static_cast<AircraftType>(type), spawnDistance);
			m_world.sortEnemies();
			break;
		}
		case Engine::Server::MissionSuccess:
			requestStackPush(StateId::MissionSuccess);
			break;
		case Engine::Server::SpawnPickup:
		{
			sf::Int32 type;
			sf::Vector2f position;
			packet >> type >> position.x >> position.y;
			m_world.createPickUp(position, static_cast<PickupType>(type));
			break;
		}
		case Engine::Server::UpdateClientState:
		{
			float currentWorldPosition;
			sf::Int32 aircraftCount;
			packet >> currentWorldPosition >> aircraftCount;
			float currentViewPosition = m_world.getViewBounds().top + m_world.getViewBounds().height;
			// Adjust world scroll compensation based on current view and world positions.
			m_world.setWorldScrollCompensation(currentViewPosition / currentWorldPosition);
			for (sf::Int32 i = 0; i < aircraftCount; ++i)
			{
				sf::Vector2f aircraftPosition;
				sf::Int32 aircraftIdentifier;
				packet >> aircraftIdentifier >> aircraftPosition.x >> aircraftPosition.y;
				Aircraft* aircraft = m_world.getAircraft(aircraftIdentifier);
				bool isLocalPlane =
					std::find(m_localPlayerIdentifiers.begin(), m_localPlayerIdentifiers.end(), aircraftIdentifier)
						!= m_localPlayerIdentifiers.end();
				if (aircraft && !isLocalPlane)
				{
					// Interpolate aircraft position for smooth updates.
					sf::Vector2f interpolatedPosition =
						aircraft->getPosition() + (aircraftPosition - aircraft->getPosition()) * 0.1f;
					aircraft->setPosition(interpolatedPosition);
				}
			}
			break;
		}
		}
	}
}