//
// Created by Johnnie Otis on 9/2/24.
//
#include "StateStack.h"

StateStack::StateStack(State::Context context)
{

}
void StateStack::draw()
{

}
void StateStack::handleEvent(const sf::Event& event)
{

}
void StateStack::pushState(StateId stateId)
{

}
void StateStack::popState()
{

}
void StateStack::update(sf::Time dt)
{

}
void StateStack::clearStates()
{

}
bool StateStack::isEmpty() const
{
	return false;
}
State::Ptr StateStack::createState(StateId stateId)
{
	return State::Ptr();
}
void StateStack::applyPendingChanges()
{

}
template<typename T>
void StateStack::registerState(StateId stateId)
{

}
