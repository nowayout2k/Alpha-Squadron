//
// Created by Johnnie Otis on 10/12/24.
//

#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_

#include "State.h"

class PauseState : public State
{
 public:
	PauseState(StateStack& stack, Context context) : State(stack, context) {};
	virtual void render(sf::RenderStates& states) override;
	virtual bool update(float deltaTime) override;
	virtual bool handleEvent(const sf::Event& event) override;

 private:
	sf::Text m_pausedText;
	sf::Text m_instructionText;
};

#endif //PAUSESTATE_H_
