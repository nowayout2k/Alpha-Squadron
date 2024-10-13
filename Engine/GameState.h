//
// Created by Johnnie Otis on 10/12/24.
//

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "State.h"
#include "World.h"

class GameState : public State
{
 public:
	GameState(StateStack& stack, State::Context context) : State(stack, context), m_world(*context.window){}
	virtual void render() override;
	virtual bool update(float deltaTime) override;
	virtual bool handleEvent(const sf::Event& event) override;
 private:
	World m_world;
};

#endif //GAMESTATE_H_
