//
// Created by Johnnie Otis on 10/12/24.
//

#include "PauseState.h"
void PauseState::render()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));
	window.draw(backgroundShape);
	window.draw(m_pausedText);
	window.draw(m_instructionText);
}
bool PauseState::update(float deltaTime)
{
	return false;
}
bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::BackSpace)
	{
		requestStateClear();
		requestStackPush(Menu);
	}
	return false;
}
