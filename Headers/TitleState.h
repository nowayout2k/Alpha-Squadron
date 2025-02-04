// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"

class TitleState : public State
{
 public:
	TitleState(StateStack& stack, Context context);
	void render(sf::RenderStates& states) override;
	bool update(float deltaTime) override;
	bool handleEvent(const sf::Event& event) override;
 private:

	sf::Sprite m_backgroundSprite;

	sf::Text m_continueText;
	sf::Text m_companyNameText;
	bool m_showText;
	float m_textEffectTime;
};

#endif //TITLESTATE_H_
