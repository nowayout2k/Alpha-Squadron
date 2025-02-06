// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"

class TitleState : public State
{
 public:
	TitleState(StateStack& stack, Context context);
	void render(sf::RenderStates& states) override;
	bool update(sf::Time deltaTime) override;
	bool handleEvent(const sf::Event& event) override;
 private:

	sf::Sprite m_backgroundSprite;
	sf::Sprite m_logoSprite;
	sf::Text m_continueText;

	bool m_showText;
	float m_textEffectTime;
};

#endif //TITLESTATE_H_
