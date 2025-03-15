//
// Created by Johnnie on 3/14/2025.
//

#include "../Headers/KeyBinding.h"
#include <string>
#include <algorithm>


KeyBinding::KeyBinding(int controlPreconfiguration) : m_keyMap()
{
	// Set initial key bindings for player 1
	if (controlPreconfiguration == 1)
	{
		m_keyMap[sf::Keyboard::Left] = LocalPlayerAction::AccelerateNegX;
		m_keyMap[sf::Keyboard::Right] = LocalPlayerAction::AcceleratePosX;
		m_keyMap[sf::Keyboard::Up]    = LocalPlayerAction::AccelerateNegY;
		m_keyMap[sf::Keyboard::Down]  = LocalPlayerAction::AcceleratePosY;
		m_keyMap[sf::Keyboard::Space] = LocalPlayerAction::Fire;
		m_keyMap[sf::Keyboard::M]     = LocalPlayerAction::LaunchMissile;
	}
	else if (controlPreconfiguration == 2)
	{
		// Player 2
		m_keyMap[sf::Keyboard::A] = LocalPlayerAction::AccelerateNegX;
		m_keyMap[sf::Keyboard::D] = LocalPlayerAction::AcceleratePosX;
		m_keyMap[sf::Keyboard::W] = LocalPlayerAction::AccelerateNegY;
		m_keyMap[sf::Keyboard::S] = LocalPlayerAction::AcceleratePosY;
		m_keyMap[sf::Keyboard::F] = LocalPlayerAction::Fire;
		m_keyMap[sf::Keyboard::R] = LocalPlayerAction::LaunchMissile;
	}
}

void KeyBinding::assignKey(ActionType action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = m_keyMap.begin(); itr != m_keyMap.end(); )
	{
		if (itr->second == action)
			m_keyMap.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	m_keyMap[key] = action;
}

sf::Keyboard::Key KeyBinding::getAssignedKey(ActionType action) const
{
	for(auto& pair : m_keyMap)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

bool KeyBinding::checkAction(sf::Keyboard::Key key, ActionType& out) const
{
	auto found = m_keyMap.find(key);
	if (found == m_keyMap.end())
	{
		return false;
	}
	else
	{
		out = found->second;
		return true;
	}
}

std::vector<KeyBinding::ActionType> KeyBinding::getRealtimeActions() const
{
	// Return all realtime actions that are currently active.
	std::vector<ActionType> actions;

	for(auto& pair : m_keyMap)
	{
		// If key is pressed and an action is a realtime action, store it
		if (sf::Keyboard::isKeyPressed(pair.first) && IsRealtimeAction(pair.second))
			actions.push_back(pair.second);
	}

	return actions;
}

bool IsRealtimeAction(LocalPlayerAction::ActionType action)
{
	switch (action)
	{
	case LocalPlayerAction::AccelerateNegX:
	case LocalPlayerAction::AcceleratePosX:
	case LocalPlayerAction::AccelerateNegY:
	case LocalPlayerAction::AcceleratePosY:
	case LocalPlayerAction::Fire:
		return true;

	default:
		return false;
	}
}