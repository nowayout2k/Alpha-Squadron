// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include <SFML/Network/Packet.hpp>
#include "../Headers/Player.h"

std::vector<Player::ActionType> Player::m_realTimeActionTypes;

struct AircraftMover
{
	AircraftMover(float vx, float vy, int identifier) : m_velocity(vx, vy), aircraftId(identifier) {}
	explicit AircraftMover(const sf::Vector2f& mVelocity, int identifier) : m_velocity(mVelocity), aircraftId(identifier)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time dt) const
	{
		if (aircraft.getIdentifier() == aircraftId)
			aircraft.accelerate(m_velocity * aircraft.getMaxSpeed());
	}

 private:
	sf::Vector2f m_velocity;
	int aircraftId;
};


struct AircraftFireTrigger
{
	explicit AircraftFireTrigger(int identifier) : aircraftId(identifier)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		if (aircraft.getIdentifier() == aircraftId)
			aircraft.fire();
	}

	int aircraftId;
};

struct AircraftMissileTrigger
{
	explicit AircraftMissileTrigger(int identifier) : aircraftId(identifier)
	{
	}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		if (aircraft.getIdentifier() == aircraftId)
			aircraft.launchMissile();
	}

	int aircraftId;
};

Player::Player(sf::TcpSocket* socket, sf::Int32 identifier, const KeyBinding* binding)
	: m_keyBinding(binding)
	, m_missionStatus(MissionStatus::None)
	, m_identifier(identifier)
	, m_socket(socket)
{
	m_missionStatus = Player::MissionStatus::None;
	m_realTimeActionTypes.push_back(ActionType::AccelerateNegX);
	m_realTimeActionTypes.push_back(ActionType::AcceleratePosX);
	m_realTimeActionTypes.push_back(ActionType::AccelerateNegY);
	m_realTimeActionTypes.push_back(ActionType::AcceleratePosY);
	m_realTimeActionTypes.push_back(ActionType::Fire);

	m_actionBinding[ActionType::AccelerateNegX].Action = DerivedAction<Aircraft>(AircraftMover(-1, 0, identifier));
	m_actionBinding[ActionType::AcceleratePosX].Action = DerivedAction<Aircraft>(AircraftMover(1, 0, identifier));
	m_actionBinding[ActionType::AccelerateNegY].Action = DerivedAction<Aircraft>(AircraftMover(0, -1, identifier));
	m_actionBinding[ActionType::AcceleratePosY].Action = DerivedAction<Aircraft>(AircraftMover(0, 1, identifier));
 	m_actionBinding[ActionType::Fire].Action = DerivedAction<Aircraft>(AircraftFireTrigger(identifier));
	m_actionBinding[ActionType::LaunchMissile].Action = DerivedAction<Aircraft>(AircraftMissileTrigger(identifier));

	for(auto& pair : m_actionBinding)
		pair.second.NodeType = (unsigned int)NodeType::Player;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		ActionType action;
		if (m_keyBinding && m_keyBinding->checkAction(event.key.code, action) && !isRealtimeAction(action))
		{
			// Network connected -> send event over network
			if (m_socket)
			{
				sf::Packet packet;
				packet << static_cast<sf::Int32>(Client::PlayerEvent);
				packet << m_identifier;
				packet << static_cast<sf::Int32>(action);
				m_socket->send(packet);
			}
			// Network disconnected -> local event
			else
			{
				commands.push(m_actionBinding[action]);
			}
		}
	}
	// Realtime change (network connected)
	if ((event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) && m_socket)
	{
		ActionType action;
		if (m_keyBinding && m_keyBinding->checkAction(event.key.code, action) && isRealtimeAction(action))
		{
			// Send realtime change over network
			sf::Packet packet;
			packet << static_cast<sf::Int32>(Client::PlayerRealtimeChange);
			packet << m_identifier;
			packet << static_cast<sf::Int32>(action);
			packet << (event.type == sf::Event::KeyPressed);
			m_socket->send(packet);
		}
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.NodeType |= (int)NodeType::Player;
		output.Action = [] (WorldNode& worldNode, sf::Time dt)
		{
		  std::cout << worldNode.getPosition().x << ","
					<< worldNode.getPosition().y;
		};
		commands.push(output);
	}
	if (event.type == sf::Event::Resized)
	{
		Debug::log("Window resized to " + std::to_string(event.size.width) + "x" + std::to_string(event.size.height));
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::F)
		Debug::toggleFps();

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::C)
		Debug::toggleDrawColliders();
}

bool Player::isRealtimeAction(ActionType actionType)
{
	return std::any_of(m_realTimeActionTypes.begin(), m_realTimeActionTypes.end(), [actionType](ActionType at) { return actionType == at; });
}

bool Player::isLocal() const
{
	// No key binding means this player is remote
	return m_keyBinding != nullptr;
}

void Player::disableAllRealtimeActions()
{
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
	// Check if this is a networked game and local player or just a single player game
	if ((m_socket && isLocal()) || !m_socket)
	{
		// Lookup all actions and push corresponding commands to queue
		std::vector<ActionType> activeActions = m_keyBinding->getRealtimeActions();
		for(ActionType action : activeActions)
			commands.push(m_actionBinding[action]);
	}
}

void Player::handleRealtimeNetworkInput(CommandQueue& commands)
{
	if (m_socket && !isLocal())
	{
		// Traverse all realtime input proxies. Because this is a networked game, the input isn't handled directly
		for(auto& pair : m_actionProxies)
		{
			if (pair.second && isRealtimeAction(pair.first))
				commands.push(m_actionBinding[pair.first]);
		}
	}
}

void Player::handleNetworkEvent(ActionType action, CommandQueue& commands)
{
	commands.push(m_actionBinding[action]);
}

void Player::handleNetworkRealtimeChange(ActionType action, bool actionEnabled)
{
	m_actionProxies[action] = actionEnabled;
}
