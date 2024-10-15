//
// Created by Johnnie Otis on 9/2/24.
//
#include "StateStack.h"

StateStack::StateStack(State::Context context) : m_context(context)
{

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

void StateStack::render()
{
	for(auto itr = m_stack.begin(); itr != m_stack.end(); ++itr)
	{
		(*itr)->render();
	}
}

void StateStack::handleEvent(const sf::Event& event)
{
	for(auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
	{
		if(!(*itr)->handleEvent(event))
			return;
	}
	applyPendingChanges();
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
		Debug::logError("Unable to find the state id: " + std::to_string(stateId));
		return nullptr;
	}
	return found->second();
}

void StateStack::applyPendingChanges()
{
	for(auto& change : m_pendingList)
	{
		switch(change.stackActionType)
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
