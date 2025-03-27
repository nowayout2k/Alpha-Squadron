//
// Created by Johnnie on 3/14/2025.
//

#include "../Headers/KeyBinding.h"
#include <string>
#include <algorithm>

KeyBinding::KeyBinding(int controlPreconfiguration)
	: m_keyMap()
{
	// Set initial key bindings for player 1
	if (controlPreconfiguration == 1)
	{
		m_keyMap[sf::Keyboard::Left]  = LocalPlayerAction::AccelerateNegX;
		m_keyMap[sf::Keyboard::Right] = LocalPlayerAction::AcceleratePosX;
		m_keyMap[sf::Keyboard::Up]    = LocalPlayerAction::AccelerateNegY;
		m_keyMap[sf::Keyboard::Down]  = LocalPlayerAction::AcceleratePosY;
		m_keyMap[sf::Keyboard::Space] = LocalPlayerAction::Fire;
		m_keyMap[sf::Keyboard::M]     = LocalPlayerAction::LaunchMissile;
	}
	else if (controlPreconfiguration == 2)
	{
		// Player 2 key bindings
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
	// Remove all keys that already map to the given action.
	for (auto itr = m_keyMap.begin(); itr != m_keyMap.end(); )
	{
		if (itr->second == action)
			m_keyMap.erase(itr++);
		else
			++itr;
	}
	// Insert the new binding.
	m_keyMap[key] = action;
}

sf::Keyboard::Key KeyBinding::getAssignedKey(ActionType action) const
{
	for (const auto& pair : m_keyMap)
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
		return false;
	out = found->second;
	return true;
}

std::vector<KeyBinding::ActionType> KeyBinding::getRealtimeActions() const
{
	std::vector<ActionType> actions;
	// Return all realtime actions that are currently active.
	for (const auto& pair : m_keyMap)
	{
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
