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
	GameOverState(StateStack& stack, Context context, const std::string& text);
	virtual void render() override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;
 private:
	sf::Text m_gameOverText;
	float m_elapsedTime;
};

#endif //GAMEOVERSTATE_H_
