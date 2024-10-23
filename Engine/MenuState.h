//
// Created by Johnnie Otis on 10/12/24.
//

#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "StateStack.h"
#include "Container.h"

class MenuState : public State
{
 public:
	explicit MenuState(StateStack& stack, Context context);
	virtual void render(sf::RenderStates& states) override;
	virtual bool update(float deltaTime) override;
	virtual bool handleEvent(const sf::Event& event) override;
 private:
	sf::Sprite m_backgroundSprite;
	GUI::Container m_guiContainer;
};

#endif //MAINMENUSTATE_H_
