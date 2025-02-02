// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include "../Headers/State.h"
#include "../Headers/StateStack.h"

void State::requestStackPush(StateId stateId)
{
	m_stack->pushState(stateId);
}
void State::requestStackPop()
{
	m_stack->popState();
}
void State::requestStateClear()
{
	m_stack->clearStates();
}
