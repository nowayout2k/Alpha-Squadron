//
// Created by Johnnie Otis on 10/12/24.
//

#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"

class TitleState : public State
{
 public:
	TitleState(StateStack& stack, Context context);
	virtual void render(sf::RenderStates& states) override;
	virtual bool update(float deltaTime) override;
	virtual bool handleEvent(const sf::Event& event) override;
 private:
	sf::Sprite m_backgroundSprite;
	sf::Text m_text;
	bool m_showText;
	float m_textEffectTime;
};

#endif //TITLESTATE_H_
