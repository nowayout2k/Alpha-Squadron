//
// Created by Johnnie Otis on 6/13/24.
//

#include <SFML/Window/Event.hpp>
#include "../Header/Game.h"

#define FRAME_RATE_LIMIT 60.0f
#define TIME_STEP_MAX 1.0f/FRAME_RATE_LIMIT

Game::Game() : m_isPaused(false)
{
	createWindow(sf::VideoMode(1740,1000), "Alpha Squadron", sf::Style::None);
	m_world = std::make_unique<World>(m_window);
}

void Game::run()
{
	Debug::init(m_world.get());
	sf::Clock clock;
	float timeStep = 0;

	while (m_window.isOpen())
	{
		timeStep += clock.restart().asSeconds();
		while (timeStep > TIME_STEP_MAX)
		{
			timeStep -= TIME_STEP_MAX;
			processInput();
			if(!m_isPaused)
				update(TIME_STEP_MAX);
		}
		render();
	}
}

void Game::update(float deltaTime)
{
	Debug::update(deltaTime);

	m_world->update(deltaTime);
}
void Game::render()
{
	sf::RenderStates states;
	m_window.clear();

	m_world->render(m_window, states);
	Debug::render(m_window, states);

	m_window.display();

}

void Game::createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style)
{
	m_window.create(mode, title, style);
	m_window.setFramerateLimit(FRAME_RATE_LIMIT);
	m_window.setPosition(sf::Vector2i(0,0));
	m_window.setMouseCursorVisible(false);
	m_window.setVerticalSyncEnabled(false);
	m_window.setActive(true);
}

void Game::processInput()
{
	CommandQueue& commands = m_world->getCommandQueue();
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		m_player.handleEvent(event, commands);

		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)
			m_window.close();

		if (event.type == sf::Event::LostFocus)
		{
			Debug::log("Window lost focus");
			m_isPaused = true;
		}

		if (event.type == sf::Event::GainedFocus)
		{
			Debug::log("Window gained focus");
			m_isPaused = false;
		}
	}
	m_player.handleRealtimeInput(commands);
}
