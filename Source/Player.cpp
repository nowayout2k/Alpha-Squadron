// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file Player.cpp
 * @brief Implements the Player class methods.
 *
 * This source file provides the implementation for processing player input,
 * handling network events, and dispatching commands related to player actions.
 */

#include <SFML/Network/Packet.hpp>
#include "../Headers/Player.h"

// Initialize the static vector for realtime action types.
std::vector<Player::ActionType> Player::m_realTimeActionTypes;

/**
 * Functor to move an aircraft.
 * Multiplies a unit vector by the aircraft's maximum speed to accelerate it.
 */
struct AircraftMover
{
	AircraftMover(float vx, float vy, int identifier)
		: m_velocity(vx, vy), aircraftId(identifier) {}
	explicit AircraftMover(const sf::Vector2f& mVelocity, int identifier)
		: m_velocity(mVelocity), aircraftId(identifier)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time dt) const
	{
		if (aircraft.getIdentifier() == aircraftId)
			aircraft.accelerate(m_velocity * aircraft.getMaxSpeed());
	}

 private:
	sf::Vector2f m_velocity; ///< The directional unit vector for acceleration.
	int aircraftId;          ///< Identifier to match the aircraft.
};

/**
 * Functor to trigger the aircraft's fire action.
 */
struct AircraftFireTrigger
{
	explicit AircraftFireTrigger(int identifier) : aircraftId(identifier) {}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		if (aircraft.getIdentifier() == aircraftId)
			aircraft.fire();
	}

	int aircraftId; ///< Identifier to match the aircraft.
};

/**
 * Functor to trigger the aircraft's missile launch action.
 */
struct AircraftMissileTrigger
{
	explicit AircraftMissileTrigger(int identifier) : aircraftId(identifier) {}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		if (aircraft.getIdentifier() == aircraftId)
			aircraft.launchMissile();
	}

	int aircraftId; ///< Identifier to match the aircraft.
};

Player::Player(sf::TcpSocket* socket, sf::Int32 identifier, const KeyBinding* binding)
	: m_keyBinding(binding)
	, m_missionStatus(MissionStatus::None)
	, m_identifier(identifier)
	, m_socket(socket)
{
	// Initialize mission status.
	m_missionStatus = Player::MissionStatus::None;

	// Register realtime action types.
	m_realTimeActionTypes.push_back(ActionType::AccelerateNegX);
	m_realTimeActionTypes.push_back(ActionType::AcceleratePosX);
	m_realTimeActionTypes.push_back(ActionType::AccelerateNegY);
	m_realTimeActionTypes.push_back(ActionType::AcceleratePosY);
	m_realTimeActionTypes.push_back(ActionType::Fire);

	// Bind commands for various actions using corresponding functors.
	m_actionBinding[ActionType::AccelerateNegX].Action = DerivedAction<Aircraft>(AircraftMover(-1, 0, identifier));
	m_actionBinding[ActionType::AcceleratePosX].Action = DerivedAction<Aircraft>(AircraftMover(1, 0, identifier));
	m_actionBinding[ActionType::AccelerateNegY].Action = DerivedAction<Aircraft>(AircraftMover(0, -1, identifier));
	m_actionBinding[ActionType::AcceleratePosY].Action = DerivedAction<Aircraft>(AircraftMover(0, 1, identifier));
	m_actionBinding[ActionType::Fire].Action = DerivedAction<Aircraft>(AircraftFireTrigger(identifier));
	m_actionBinding[ActionType::LaunchMissile].Action = DerivedAction<Aircraft>(AircraftMissileTrigger(identifier));

	// Set node type for all action commands to Player.
	for(auto& pair : m_actionBinding)
		pair.second.NodeType = (unsigned int)NodeType::Player;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	// Process discrete key press events.
	if (event.type == sf::Event::KeyPressed)
	{
		ActionType action;
		if (m_keyBinding && m_keyBinding->checkAction(event.key.code, action) && !isRealtimeAction(action))
		{
			// If connected over network, send the event packet.
			if (m_socket)
			{
				sf::Packet packet;
				packet << static_cast<sf::Int32>(Client::PlayerEvent);
				packet << m_identifier;
				packet << static_cast<sf::Int32>(action);
				m_socket->send(packet);
			}
				// Otherwise, push the command locally.
			else
			{
				commands.push(m_actionBinding[action]);
			}
		}
	}
	// Handle realtime action changes for networked players.
	if ((event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) && m_socket)
	{
		ActionType action;
		if (m_keyBinding && m_keyBinding->checkAction(event.key.code, action) && isRealtimeAction(action))
		{
			sf::Packet packet;
			packet << static_cast<sf::Int32>(Client::PlayerRealtimeChange);
			packet << m_identifier;
			packet << static_cast<sf::Int32>(action);
			packet << (event.type == sf::Event::KeyPressed);
			m_socket->send(packet);
		}
	}
	// Special case: Print aircraft position on pressing 'P'.
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.NodeType |= (int)NodeType::Player;
		output.Action = [] (WorldNode& worldNode, sf::Time dt)
		{
		  std::cout << worldNode.getPosition().x << "," << worldNode.getPosition().y;
		};
		commands.push(output);
	}
	// Log window resize events.
	if (event.type == sf::Event::Resized)
	{
		Debug::log("Window resized to " + std::to_string(event.size.width) + "x" + std::to_string(event.size.height));
	}
	// Toggle debug options on specific key presses.
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F)
		Debug::toggleFps();
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
		Debug::toggleDrawColliders();
}

bool Player::isRealtimeAction(ActionType actionType)
{
	// Check if the provided action type exists in the realtime actions list.
	return std::any_of(m_realTimeActionTypes.begin(), m_realTimeActionTypes.end(), [actionType](ActionType at) { return actionType == at; });
}

bool Player::isLocal() const
{
	// A non-null key binding indicates a local player.
	return m_keyBinding != nullptr;
}

void Player::disableAllRealtimeActions()
{
	// For each realtime action proxy, send a packet to disable the action.
	for(auto& action : m_actionProxies)
	{
		sf::Packet packet;
		packet << static_cast<sf::Int32>(Client::PlayerRealtimeChange);
		packet << m_identifier;
		packet << static_cast<sf::Int32>(action.first);
		packet << false;
		m_socket->send(packet);
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Process realtime input for local players (or when in single-player mode).
	if ((m_socket && isLocal()) || !m_socket)
	{
		std::vector<ActionType> activeActions = m_keyBinding->getRealtimeActions();
		for(ActionType action : activeActions)
			commands.push(m_actionBinding[action]);
	}
}

void Player::handleRealtimeNetworkInput(CommandQueue& commands)
{
	// For remote players, push commands based on the state of realtime action proxies.
	if (m_socket && !isLocal())
	{
		for(auto& pair : m_actionProxies)
		{
			if (pair.second && isRealtimeAction(pair.first))
				commands.push(m_actionBinding[pair.first]);
		}
	}
}

void Player::handleNetworkEvent(ActionType action, CommandQueue& commands)
{
	// Directly push the command associated with the network event.
	commands.push(m_actionBinding[action]);
}

void Player::handleNetworkRealtimeChange(ActionType action, bool actionEnabled)
{
	// Update the state of the realtime action proxy.
	m_actionProxies[action] = actionEnabled;
}
