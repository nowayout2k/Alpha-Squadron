//
// Created by Johnnie Otis on 8/12/24.
//

#include "Player.h"

std::vector<Player::ActionType> Player::m_realTimeActionTypes;

Player::Player()
{
	m_realTimeActionTypes.push_back(AccelerateNegX);
	m_realTimeActionTypes.push_back(AcceleratePosX);
	m_realTimeActionTypes.push_back(AccelerateNegY);
	m_realTimeActionTypes.push_back(AcceleratePosY);
	//m_realTimeActionTypes.push_back(Fire);

	assignKey(AccelerateNegX, sf::Keyboard::Left);
	assignKey(AcceleratePosX, sf::Keyboard::Right);
	assignKey(AccelerateNegY, sf::Keyboard::Up);
	assignKey(AcceleratePosY, sf::Keyboard::Down);
	assignKey(Fire, sf::Keyboard::Space);
	assignKey(LaunchMissile, sf::Keyboard::M);

	m_actionBinding[AccelerateNegX].Action = DerivedAction<Aircraft>(AircraftMover(-1, 0));
	m_actionBinding[AcceleratePosX].Action = DerivedAction<Aircraft>(AircraftMover(1, 0));
	m_actionBinding[AccelerateNegY].Action = DerivedAction<Aircraft>(AircraftMover(0, -1));
	m_actionBinding[AcceleratePosY].Action = DerivedAction<Aircraft>(AircraftMover(0, 1));
 	m_actionBinding[Fire].Action = DerivedAction<Aircraft>([](Aircraft& a, float)
	{ a.fire(); });
	m_actionBinding[LaunchMissile].Action = DerivedAction<Aircraft>([](Aircraft& a, float)
	{ a.launchMissile(); });

	for(auto& pair : m_actionBinding)
		pair.second.NodeType = (unsigned int)NodeType::Player;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = m_keyBinding.find(event.key.code);
		if (found != m_keyBinding.end() && !isRealtimeAction(found->second))
			commands.push(m_actionBinding[found->second]);
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.NodeType |= (int)NodeType::Player;
		output.Action = [] (WorldNode& worldNode, float dt)
		{
		  std::cout << worldNode.getPosition().x << ","
					<< worldNode.getPosition().y << "\n";
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

void Player::handleRealtimeInput(CommandQueue& commands)
{
	for(auto pair : m_keyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
		{
			commands.push(m_actionBinding[pair.second]);
		}
	}
}

void Player::assignKey(ActionType actionType, sf::Keyboard::Key key)
{
	std::vector<sf::Keyboard::Key> keysPendingRemoval;
	for (auto& keyBinding : m_keyBinding)
	{
		if(keyBinding.second == actionType)
			keysPendingRemoval.push_back(keyBinding.first);
	}

	for (auto keyPendingRemoval : keysPendingRemoval)
	{
		m_keyBinding.erase(keyPendingRemoval);
		Debug::log("This Action Type has already been assigned to " + std::to_string(keyPendingRemoval) + ". Replacing it with " + std::to_string(key) + ".");
	}

	m_keyBinding[key] = actionType;
}

sf::Keyboard::Key Player::getAssignedKey(ActionType actionType) const
{
	for (auto& keyBinding : m_keyBinding)
	{
		if(keyBinding.second == actionType)
			return keyBinding.first;
	}

	Debug::logError("Cannot get the assigned key because it could not be found!");

	return sf::Keyboard::Key::KeyCount;
}

bool Player::isRealtimeAction(ActionType actionType)
{
	return std::any_of(m_realTimeActionTypes.begin(), m_realTimeActionTypes.end(), [actionType](ActionType at) { return actionType == at; });
}

