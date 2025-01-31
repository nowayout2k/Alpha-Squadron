//
// Created by Johnnie Otis on 10/12/24.
//
#include "State.h"
#include "StateStack.h"

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
