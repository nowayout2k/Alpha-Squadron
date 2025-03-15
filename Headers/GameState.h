// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "State.h"
#include "World.h"

class GameState : public State
{
 public:
	GameState(StateStack& stack, State::Context context);
	void render() override;
	bool update(sf::Time deltaTime) override;
	bool handleEvent(const sf::Event& event) override;
 private:
	World m_world;
	Player m_player;
};

#endif //GAMESTATE_H_
