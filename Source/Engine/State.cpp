// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file State.cpp
 * @brief Implements helper functions for the State class.
 *
 * This source file provides the implementations for functions that modify the state stack,
 * such as pushing, popping, and clearing states.
 */

#include "../../Headers/Engine/State.h"
#include "../../Headers/Engine/StateStack.h"
namespace Engine
{
	void State::requestStackPush(AlphaSquadron::StateId stateId)
	{
		// Request the state stack to push a new state identified by stateId.
		m_stack->pushState(stateId);
	}

	void State::requestStackPop()
	{
		// Request the state stack to remove the current state.
		m_stack->popState();
	}

	void State::requestStateClear()
	{
		// Request the state stack to clear all states.
		m_stack->clearStates();
	}
}