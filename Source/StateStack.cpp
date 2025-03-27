// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file StateStack.cpp
 * @brief Implementation of the StateStack class.
 *
 * This source file implements the functions of the StateStack class, including state
 * updates, event handling, and pending change processing.
 */

#include "../Headers/StateStack.h"

StateStack::StateStack(State::Context context) : m_context(context)
{
	// Populate m_allKeys with all possible keyboard keys.
	for (int key = 0; key <= sf::Keyboard::KeyCount; ++key)
	{
		m_allKeys.push_back(static_cast<sf::Keyboard::Key>(key));
	}
}

void StateStack::pushState(StateId stateId)
{
	// Add a push action to the pending list.
	m_pendingList.emplace_back(StackActionType::Push, stateId);
}

void StateStack::popState()
{
	// Add a pop action to the pending list.
	m_pendingList.emplace_back(StackActionType::Pop);
}

void StateStack::clearStates()
{
	// Add a clear action to the pending list.
	m_pendingList.emplace_back(StackActionType::Clear);
}

bool StateStack::isEmpty() const
{
	// Return true if there are no states on the stack.
	return m_stack.empty();
}

void StateStack::render()
{
	// Render all states in the order they are stored.
	for (auto itr = m_stack.begin(); itr != m_stack.end(); ++itr)
	{
		(*itr)->render();
	}
}

void StateStack::handleEvent(const sf::Event& event)
{
	// Process rollover key events first; if handled, return immediately.
	if (handleRolloverKeyEvent(event))
		return;

	// Iterate in reverse order (topmost state first) and forward the event.
	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			return;
	}
	applyPendingChanges();
}

bool StateStack::handleRolloverKeyEvent(const sf::Event& event)
{
	// If a key is pressed and already in the rollover set, consume the event.
	if (event.type == sf::Event::KeyPressed &&
		std::find(m_rolloverPressedKeys.begin(), m_rolloverPressedKeys.end(), event.key.code) != m_rolloverPressedKeys.end())
	{
		return true;
	}
	// If a key is released and was in the rollover set, remove it and consume the event.
	if (event.type == sf::Event::KeyReleased)
	{
		auto itr = std::find(m_rolloverPressedKeys.begin(), m_rolloverPressedKeys.end(), event.key.code);
		if (itr != m_rolloverPressedKeys.end())
		{
			m_rolloverPressedKeys.erase(itr);
			return true;
		}
	}
	return false;
}

void StateStack::update(sf::Time deltaTime)
{
	// Iterate in reverse order (from top state downwards) until one state stops further updating.
	for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
	{
		if (!(*itr)->update(deltaTime))
			break;
	}
	applyPendingChanges();
}

State::Ptr StateStack::createState(StateId stateId)
{
	// Look up the factory for the given state ID.
	auto found = m_factories.find(stateId);
	if (found == m_factories.end())
	{
		Debug::logError("Unable to find the state id: " + std::to_string(static_cast<int>(stateId)));
		return nullptr;
	}
	// Create and return the state instance.
	return found->second();
}

void StateStack::applyPendingChanges()
{
	// If there are pending changes, update the rollover pressed keys to include currently pressed keys.
	if (!m_pendingList.empty())
	{
		for (auto key : m_allKeys)
		{
			if (sf::Keyboard::isKeyPressed(key))
				m_rolloverPressedKeys.insert(key);
		}
	}

	// Process each pending change.
	for (auto& change : m_pendingList)
	{
		switch (change.StackActionType)
		{
		case Push:
			m_stack.push_back(createState(change.StateId));
			break;
		case Pop:
			m_stack.pop_back();
			break;
		case Clear:
			m_stack.clear();
			ResourceManager::clearAllCache();
			break;
		}
	}
	// Clear the pending change list.
	m_pendingList.clear();
}
