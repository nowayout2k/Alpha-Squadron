// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/GameOverState.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context, const std::string& text) :
	State(stack, context) , m_gameOverText(), m_elapsedTime(0)
{
	sf::Font& font = ResourceManager::loadResource(FontId::Arnold);
	sf::Vector2f windowSize(context.Window->getSize());

	m_gameOverText.setFont(font);
	m_gameOverText.setString(text);

	m_gameOverText.setCharacterSize(70);
	Utility::centerOrigin(m_gameOverText);
	m_gameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::render()
{
	sf::RenderWindow& window = *getContext().Window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(m_gameOverText);
}

bool GameOverState::update(sf::Time dt)
{
	m_elapsedTime += dt.asSeconds();
	if (m_elapsedTime > 3)
	{
		requestStateClear();
		requestStackPush(StateId::Menu);
	}
	return false;
}

bool GameOverState::handleEvent(const sf::Event&)
{
	return false;
}
