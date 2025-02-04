// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "StateStack.h"
#include "Container.h"

class MenuState : public State
{
 public:
	explicit MenuState(StateStack& stack, Context context);
	void render(sf::RenderStates& states) override;
	bool update(float deltaTime) override;
	bool handleEvent(const sf::Event& event) override;
 private:
	sf::Sprite m_backgroundSprite;
	sf::Text m_titleText;
	GUI::Container m_guiContainer;
};

#endif //MAINMENUSTATE_H_
