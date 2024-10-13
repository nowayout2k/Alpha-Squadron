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
	virtual void render();
	virtual bool update(float deltaTime);
	virtual bool handleEvent(const sf::Event& event);
 private:
	sf::Sprite m_backgroundSprite;
	sf::Text m_text;
	bool m_showText;
	float m_textEffectTime;
};

#endif //TITLESTATE_H_
