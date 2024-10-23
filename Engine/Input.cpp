//
// Created by Johnnie Otis on 8/12/24.
//

#include "Input.h"

std::vector<Input::ActionType> Input::m_realTimeActionTypes;

Input::Input()
{
	m_realTimeActionTypes.push_back(AccelerateNegX);
	m_realTimeActionTypes.push_back(AcceleratePosX);
	m_realTimeActionTypes.push_back(AccelerateNegY);
	m_realTimeActionTypes.push_back(AcceleratePosY);

	assignKey(AccelerateNegX, sf::Keyboard::A);
	assignKey(AcceleratePosX, sf::Keyboard::D);
	assignKey(AccelerateNegY, sf::Keyboard::W);
	assignKey(AcceleratePosY, sf::Keyboard::S);

	m_actionBinding[AccelerateNegX].action = derivedAction<Aircraft>(AircraftMover(-1,  0));
	m_actionBinding[AcceleratePosX].action = derivedAction<Aircraft>(AircraftMover(1,  0));
	m_actionBinding[AccelerateNegY].action = derivedAction<Aircraft>(AircraftMover( 0, -1));
	m_actionBinding[AcceleratePosY].action = derivedAction<Aircraft>(AircraftMover( 0, 1));

	for(auto& pair : m_actionBinding)
		pair.second.nodeType = (unsigned int)NodeType::Player;
}

void Input::handleEvent(const sf::Event& event, CommandQueue& commands)
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
		output.nodeType |= (int)NodeType::Player;
		output.action = [] (WorldNode& worldNode, float dt)
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
}

void Input::handleRealtimeInput(CommandQueue& commands)
{
	for(auto pair : m_keyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
		{
			commands.push(m_actionBinding[pair.second]);
		}
	}
}

void Input::assignKey(ActionType actionType, sf::Keyboard::Key key)
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

sf::Keyboard::Key Input::getAssignedKey(ActionType actionType) const
{
	for (auto& keyBinding : m_keyBinding)
	{
		if(keyBinding.second == actionType)
			return keyBinding.first;
	}

	Debug::logError("Cannot get the assigned key because it could not be found!");

	return sf::Keyboard::Key::KeyCount;
}

bool Input::isRealtimeAction(ActionType actionType)
{
	bool isRealTime = std::any_of(m_realTimeActionTypes.begin(), m_realTimeActionTypes.end(), [actionType](ActionType at) { return actionType == at; });
	return isRealTime;
}

