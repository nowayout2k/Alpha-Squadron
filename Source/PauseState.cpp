// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/PauseState.h"
void PauseState::render()
{
	sf::RenderWindow& window = *getContext().Window;
	window.setView(window.getDefaultView());
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));
	window.draw(backgroundShape);
	window.draw(m_pausedText);
	window.draw(m_instructionText);
}
bool PauseState::update(sf::Time deltaTime)
{
	return false;
}
bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::BackSpace)
	{
		requestStateClear();
		requestStackPush(StateId::Menu);
	}
	return false;
}
