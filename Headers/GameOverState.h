// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef GAMEOVERSTATE_H_
#define GAMEOVERSTATE_H_


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include "StateStack.h"

class GameOverState : public State
{
 public:
	GameOverState(StateStack& stack, Context context);
	virtual void render(sf::RenderStates& states) override;
	virtual bool update(float dt) override;
	virtual bool handleEvent(const sf::Event& event) override;
 private:
	sf::Text m_gameOverText;
	float m_elapsedTime;
};

#endif //GAMEOVERSTATE_H_
