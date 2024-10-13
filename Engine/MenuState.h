//
// Created by Johnnie Otis on 10/12/24.
//

#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "StateStack.h"

class MenuState : public State
{
 public:
	enum OptionNames
	{
		Play,
		Exit,
	};
	MenuState(StateStack& stack, Context context);
	virtual void render();
	virtual bool update(float deltaTime);
	virtual bool handleEvent(const sf::Event& event);
	void updateOptionText();
 private:
	sf::Sprite m_backgroundSprite;
	std::vector<sf::Text> m_options;
	std::size_t m_optionIndex;
};

#endif //MAINMENUSTATE_H_
