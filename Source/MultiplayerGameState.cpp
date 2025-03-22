//
// Created by Johnnie on 2/20/2025.
//

#include "../Headers/MultiplayerGameState.h"
#include "../Headers/NetworkProtocol.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Network/IpAddress.hpp>

#include <fstream>
#include <memory>

sf::IpAddress GetAddressFromFile()
{
	{
		std::ifstream inputFile("ip.txt");
		std::string ipAddress;
		if (inputFile >> ipAddress)
			return ipAddress;
	}

	// If open/read failed, create new file
	std::ofstream outputFile("ip.txt");
	std::string localAddress = "127.0.0.1";
	outputFile << localAddress;
	return localAddress;
}

MultiplayerGameState::MultiplayerGameState(StateStack& stack, Context context, bool isHost)
	: State(stack, context)
	, m_world(*context.Window, *context.Audio, true)
	, m_window(*context.Window)
	, m_connected(false)
	, m_gameServer(nullptr)
	, m_activeState(true)
	, m_hasFocus(true)
	, m_host(isHost)
	, m_gameStarted(false)
	, m_clientTimeout(sf::seconds(2.f))
	, m_timeSinceLastPacket(sf::seconds(0.f))
{
	m_broadcastText.setFont(ResourceManager::loadResource(FontId::Arnold));
	m_broadcastText.setPosition(1024.f / 2, 100.f);

	m_playerInvitationText.setFont(ResourceManager::loadResource(FontId::Arnold));
	m_playerInvitationText.setCharacterSize(20);
	m_playerInvitationText.setFillColor(sf::Color::White);
	m_playerInvitationText.setString("Press Enter to spawn player 2");
	m_playerInvitationText.setPosition(m_window.getSize().x/2 - m_playerInvitationText.getLocalBounds().width/2, m_window.getSize().y - m_playerInvitationText.getLocalBounds().height);

	// We reuse this text for "Attempt to connect" and "Failed to connect" messages
	m_failedConnectionText.setFont(ResourceManager::loadResource(FontId::Arnold));
	m_failedConnectionText.setString("Attempting to connect...");
	m_failedConnectionText.setCharacterSize(35);
	m_failedConnectionText.setFillColor(sf::Color::White);
	Utility::centerOrigin(m_failedConnectionText);
	m_failedConnectionText.setPosition(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);

	// Render an "establishing connection" frame for user feedback
	m_window.clear(sf::Color::Black);
	m_window.draw(m_failedConnectionText);
	m_window.display();
	m_failedConnectionText.setString("Could not connect to the remote server!");
	Utility::centerOrigin(m_failedConnectionText);

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

	if (m_socket.connect(ip, ServerPort, sf::seconds(5.f)) == sf::TcpSocket::Done)
		m_connected = true;
	else
		m_failedConnectionClock.restart();

	m_socket.setBlocking(false);

	// Play game theme
	context.Audio->playMusic(MusicId::GameMusic, 12.f);
}

void MultiplayerGameState::render()
{
	if (m_connected)
	{
		m_world.render();

		// Broadcast messages in default view
		m_window.setView(m_window.getDefaultView());

		if (!m_broadcasts.empty())
			m_window.draw(m_broadcastText);

		if (m_localPlayerIdentifiers.size() < 2 && m_playerInvitationTime < sf::seconds(0.5f))
			m_window.draw(m_playerInvitationText);
	}
	else
	{
		m_window.draw(m_failedConnectionText);
	}
}

void MultiplayerGameState::onActivate()
{
	m_activeState = true;
}

void MultiplayerGameState::onDestroy()
{
	if (!m_host && m_connected)
	{
		// Inform server this client is dying
		sf::Packet packet;
		packet << static_cast<sf::Int32>(Client::Quit);
		m_socket.send(packet);
	}
}

bool MultiplayerGameState::update(sf::Time dt)
{
	// Connected to server: Handle all the network logic
	if (m_connected)
	{
		m_world.update(dt);

		// Remove players whose aircrafts were destroyed
		bool foundLocalPlane = false;
		for (auto itr = m_players.begin(); itr != m_players.end(); )
		{
			// Check if there are no more local planes for remote clients
			if (std::find(m_localPlayerIdentifiers.begin(), m_localPlayerIdentifiers.end(), itr->first) != m_localPlayerIdentifiers.end())
			{
				foundLocalPlane = true;
			}

			if (!m_world.getAircraft(itr->first))
			{
				itr = m_players.erase(itr);

				// No more players left: Mission failed
				if (m_players.empty())
					requestStackPush(StateId::GameOver);
			}
			else
			{
				++itr;
			}
		}

		if (!foundLocalPlane && m_gameStarted)
		{
			requestStackPush(StateId::GameOver);
		}

		// Only handle the realtime input if the window has focus and the game is unpaused
		if (m_activeState && m_hasFocus)
		{
			CommandQueue& commands = m_world.getCommandQueue();
			for(auto& pair :  m_players)
				pair.second->handleRealtimeInput(commands);
		}

		// Always handle the network input
		CommandQueue& commands = m_world.getCommandQueue();
		for(auto& pair : m_players)
			pair.second->handleRealtimeNetworkInput(commands);

		// Handle messages from server that may have arrived
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
				// Check for timeout with the server
				if (m_timeSinceLastPacket > m_clientTimeout)
				{
					m_connected = false;

					m_failedConnectionText.setString("Lost connection to server");
					Utility::centerOrigin(m_failedConnectionText);

					m_failedConnectionClock.restart();
				}
			}
		}

		updateBroadcastMessage(dt);

		// Time counter for blinking 2nd player text
		m_playerInvitationTime += dt;
		if (m_playerInvitationTime > sf::seconds(1.f))
			m_playerInvitationTime = sf::Time::Zero;

		// Events occurring in the game
		GameActions::Action gameAction;
		while (m_world.pollGameAction(gameAction))
		{
			sf::Packet packet;
			packet << static_cast<sf::Int32>(Client::GameEvent);
			packet << static_cast<sf::Int32>(gameAction.Type);
			packet << gameAction.Position.x;
			packet << gameAction.Position.y;

			m_socket.send(packet);
		}

		// Regular position updates
		if (m_tickClock.getElapsedTime() > sf::seconds(1.f / 20.f))
		{
			sf::Packet positionUpdatePacket;
			positionUpdatePacket << static_cast<sf::Int32>(Client::PositionUpdate);
			positionUpdatePacket << static_cast<sf::Int32>(m_localPlayerIdentifiers.size());

			for(sf::Int32 identifier : m_localPlayerIdentifiers)
			{
				if (Aircraft* aircraft = m_world.getAircraft(identifier))
					positionUpdatePacket << identifier << aircraft->getPosition().x << aircraft->getPosition().y << static_cast<sf::Int32>(aircraft->getHealth()) << static_cast<sf::Int32>(aircraft->getMissileCount());
			}

			m_socket.send(positionUpdatePacket);
			m_tickClock.restart();
		}

		m_timeSinceLastPacket += dt;
	}

		// Failed to connect and waited for more than 5 seconds: Back to menu
	else if (m_failedConnectionClock.getElapsedTime() >= sf::seconds(5.f))
	{
		requestStateClear();
		requestStackPush(StateId::Menu);
	}

	return true;
}

void MultiplayerGameState::disableAllRealtimeActions()
{
	m_activeState = false;

	for(sf::Int32 identifier : m_localPlayerIdentifiers)
		m_players[identifier]->disableAllRealtimeActions();
}

bool MultiplayerGameState::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = m_world.getCommandQueue();

	// Forward event to all players
	for(auto& pair : m_players)
		pair.second->handleEvent(event, commands);

	if (event.type == sf::Event::KeyPressed)
	{
		// Enter pressed, add second player co-op (only if we are one player)
		if (event.key.code == sf::Keyboard::Return && m_localPlayerIdentifiers.size() == 1)
		{
			sf::Packet packet;
			packet << static_cast<sf::Int32>(Client::RequestCoopPartner);

			m_socket.send(packet);
		}

			// Escape pressed, trigger the pause screen
		else if (event.key.code == sf::Keyboard::Escape)
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
	if (m_broadcasts.empty())
		return;

	// Update broadcast timer
	m_broadcastElapsedTime += elapsedTime;
	if (m_broadcastElapsedTime > sf::seconds(2.5f))
	{
		// If message has expired, remove it
		m_broadcasts.erase(m_broadcasts.begin());

		// Continue to display next broadcast message
		if (!m_broadcasts.empty())
		{
			m_broadcastText.setString(m_broadcasts.front());
			Utility::centerOrigin(m_broadcastText);
			m_broadcastElapsedTime = sf::Time::Zero;
		}
	}
}

void MultiplayerGameState::handlePacket(sf::Int32 packetType, sf::Packet& packet)
{
	switch (packetType)
	{
		case Server::BroadcastMessage:
		{
			std::string message;
			packet >> message;
			m_broadcasts.push_back(message);

			// Just added first message, display immediately
			if (m_broadcasts.size() == 1)
			{
				m_broadcastText.setString(m_broadcasts.front());
				Utility::centerOrigin(m_broadcastText);
				m_broadcastElapsedTime = sf::Time::Zero;
			}
			break;
		}
		case Server::SpawnSelf:
		{
			sf::Int32 aircraftIdentifier;
			sf::Vector2f aircraftPosition;
			packet >> aircraftIdentifier >> aircraftPosition.x >> aircraftPosition.y;
			Aircraft* aircraft = m_world.addAircraft(aircraftIdentifier);
			aircraft->setPosition(aircraftPosition);
			m_players[aircraftIdentifier].reset(new Player(&m_socket, aircraftIdentifier, getContext().KeysPlayer1));
			m_localPlayerIdentifiers.push_back(aircraftIdentifier);
			m_gameStarted = true;
			break;
		}
		case Server::PlayerConnect:
		{
			sf::Int32 aircraftIdentifier;
			sf::Vector2f aircraftPosition;
			packet >> aircraftIdentifier >> aircraftPosition.x >> aircraftPosition.y;
			Aircraft* aircraft = m_world.addAircraft(aircraftIdentifier);
			aircraft->setPosition(aircraftPosition);
			m_players[aircraftIdentifier].reset(new Player(&m_socket, aircraftIdentifier, nullptr));
			break;
		}
		case Server::PlayerDisconnect:
		{
			sf::Int32 aircraftIdentifier;
			packet >> aircraftIdentifier;

			m_world.removeAircraft(aircraftIdentifier);
			m_players.erase(aircraftIdentifier);
			break;
		}
		case Server::InitialState:
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

				Aircraft* aircraft = m_world.addAircraft(aircraftIdentifier);
				aircraft->setPosition(aircraftPosition);
				aircraft->setHealth(hitpoints);
				aircraft->changeMissileCount(missileAmmo - aircraft->getMissileCount());

				m_players[aircraftIdentifier] = std::make_unique<Player>(&m_socket, aircraftIdentifier, nullptr);
			}
			break;
		}
		case Server::AcceptCoopPartner:
		{
			sf::Int32 aircraftIdentifier;
			packet >> aircraftIdentifier;

			m_world.addAircraft(aircraftIdentifier);
			m_players[aircraftIdentifier].reset(new Player(&m_socket, aircraftIdentifier, getContext().KeysPlayer2));
			m_localPlayerIdentifiers.push_back(aircraftIdentifier);
			break;
		}
		case Server::PlayerEvent:
		{
			sf::Int32 aircraftIdentifier;
			sf::Int32 action;
			packet >> aircraftIdentifier >> action;

			auto itr = m_players.find(aircraftIdentifier);
			if (itr != m_players.end())
				itr->second->handleNetworkEvent(static_cast<LocalPlayerAction::ActionType>(action), m_world.getCommandQueue());
			break;
		}
		case Server::PlayerRealtimeChange:
		{
			sf::Int32 aircraftIdentifier;
			sf::Int32 action;
			bool actionEnabled;
			packet >> aircraftIdentifier >> action >> actionEnabled;

			auto itr = m_players.find(aircraftIdentifier);
			if (itr != m_players.end())
				itr->second->handleNetworkRealtimeChange(static_cast<LocalPlayerAction::ActionType>(action), actionEnabled);
			break;
		}
		case Server::SpawnEnemy:
		{
			sf::Int32 type;
			float relativeY;
			float spawnDistance;
			packet >> type >> spawnDistance >> relativeY;
			m_world.addEnemy(static_cast<AircraftType>(type), spawnDistance);
			m_world.sortEnemies();
			break;
		}
		case Server::MissionSuccess:
			requestStackPush(StateId::MissionSuccess);
			break;
		case Server::SpawnPickup:
		{
			sf::Int32 type;
			sf::Vector2f position;
			packet >> type >> position.x >> position.y;
			m_world.createPickUp(position, static_cast<PickupType>(type));
			break;
		}
		case Server::UpdateClientState:
		{
			float currentWorldPosition;
			sf::Int32 aircraftCount;
			packet >> currentWorldPosition >> aircraftCount;

			float currentViewPosition = m_world.getViewBounds().top + m_world.getViewBounds().height;

			// Set the world's scroll compensation according to whether the view is behind or too advanced
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
					sf::Vector2f interpolatedPosition =
						aircraft->getPosition() + (aircraftPosition - aircraft->getPosition()) * 0.1f;
					aircraft->setPosition(interpolatedPosition);
				}
			}
			break;
		}
	}
}