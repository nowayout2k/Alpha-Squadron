// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_

#include "State.h"
#include "Container.h"

class PauseState : public State
{
 public:
	PauseState(StateStack& stack, Context context, bool letUpdatesThrough = false);
	~PauseState();
	virtual void render() override;
	virtual bool update(sf::Time deltaTime) override;
	virtual bool handleEvent(const sf::Event& event) override;

 private:
	sf::Text m_pausedText;
	sf::Text m_instructionText;
	sf::Sprite m_backgroundSprite;
	GUI::Container m_guiContainer;
	bool m_letUpdatesThrough;
};

#endif //PAUSESTATE_H_
