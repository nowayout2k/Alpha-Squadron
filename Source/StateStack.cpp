// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include "../Headers/StateStack.h"

StateStack::StateStack(State::Context context) : m_context(context)
{
	for (int key = 0; key <= sf::Keyboard::KeyCount; ++key)
	{
		m_allKeys.push_back(static_cast<sf::Keyboard::Key>(key));
	}
}

void StateStack::pushState(StateId stateId)
{
	m_pendingList.push_back(PendingChange(StackActionType::Push, stateId));
}

void StateStack::popState()
{
	m_pendingList.push_back(PendingChange(StackActionType::Pop));
}

void StateStack::clearStates()
{
	m_pendingList.push_back(PendingChange(StackActionType::Clear));
}

bool StateStack::isEmpty() const
{
	return m_stack.empty();
}

void StateStack::render(sf::RenderStates& states)
{
	for(auto itr = m_stack.begin(); itr != m_stack.end(); ++itr)
	{
		(*itr)->render(states);
	}
}

void StateStack::handleEvent(const sf::Event& event)
{
	if(handleRolloverKeyEvent(event))
		return;

	for(auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
	{
		if(!(*itr)->handleEvent(event))
			return;
	}
	applyPendingChanges();
}

bool StateStack::handleRolloverKeyEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed && std::find(m_rolloverPressedKeys.begin(), m_rolloverPressedKeys.end(), event.key.code) != m_rolloverPressedKeys.end())
	{
		return true;
	}
	if (event.type == sf::Event::KeyReleased)
	{
		auto itr = std::find(m_rolloverPressedKeys.begin(), m_rolloverPressedKeys.end(), event.key.code);
		if(itr != m_rolloverPressedKeys.end())
		{
			m_rolloverPressedKeys.erase(itr);
			return true;
		}
	}
	return false;
}

void StateStack::update(float deltaTime)
{
	for(auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
	{
		if(!(*itr)->update(deltaTime))
			return;
	}
	applyPendingChanges();
}

State::Ptr StateStack::createState(StateId stateId)
{
	auto found = m_factories.find(stateId);
	if(found == m_factories.end())
	{
		Debug::logError("Unable to find the state id: " + std::to_string(static_cast<int>(stateId)));
		return nullptr;
	}
	return found->second();
}

void StateStack::applyPendingChanges()
{
	//capture keys pressed while transitioning
	if(!m_pendingList.empty())
	{
		for (auto key : m_allKeys)
		{
			if(sf::Keyboard::isKeyPressed(key))
				m_rolloverPressedKeys.insert(key);
		}
	}

	for(auto& change : m_pendingList)
	{
		switch (change.stackActionType)
		{
		case Push:
			m_stack.push_back(createState(change.stateId));
			break;
		case Pop:
			m_stack.pop_back();
			break;
		case Clear:
			m_stack.clear();
			break;
		}
	}
	m_pendingList.clear();
}
