// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/GameOverState.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context) :
	State(stack, context) , m_gameOverText(), m_elapsedTime(0)
{
	sf::Font& font = ResourceManager::loadResource(FontId::Gamer);
	sf::Vector2f windowSize(context.window->getSize());

	m_gameOverText.setFont(font);
	if (Player::getMissionStatus() == Player::MissionStatus::Failure)
		m_gameOverText.setString("Mission failed!");
	else
		m_gameOverText.setString("Mission successful!");

	m_gameOverText.setCharacterSize(70);
	Utility::centerOrigin(m_gameOverText);
	m_gameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::render(sf::RenderStates& states)
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(m_gameOverText);
}

bool GameOverState::update(float dt)
{
	m_elapsedTime += dt;
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
