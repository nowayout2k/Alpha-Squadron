//
// Created by Johnnie Otis on 9/2/24.
//

#include "State.h"
#include "StateStack.h"

State::State(StateStack& stack, State::Context context)
{

}
State::~State()
{

}
void State::requestStackPush(StateId stateId)
{

}
void State::requestStackPop()
{

}
void State::requestStateClear()
{

}
State::Context State::getContext() const
{
	return State::Context();
}
