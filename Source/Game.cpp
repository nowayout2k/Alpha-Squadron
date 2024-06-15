//
// Created by Johnnie Otis on 6/13/24.
//

#include "../Header/Game.h"
#include "../Header/Debug.h"

#define FRAME_RATE_LIMIT 120.0f
#define TIME_STEP_MAX 1.0f/FRAME_RATE_LIMIT

sf::RenderWindow Game::m_window;

void Game::run()
{
	createWindow(sf::VideoMode(1740,1000), "Alpha Squadron", sf::Style::None);
	Debug::init();

	m_scene.setup();
	sf::Clock clock;
	sf::RenderStates states;
	float timeStep = 0;

	while (m_window.isOpen())
	{
		timeStep += clock.restart().asSeconds();
		while (timeStep > TIME_STEP_MAX)
		{
			timeStep -= TIME_STEP_MAX;
			processEvents();
			update(TIME_STEP_MAX);
		}
		render(m_window, states);
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)
			m_window.close();

		if (event.type == sf::Event::Resized)
		{
			Debug::log(LogType::Verbose,"Window resized to " + std::to_string(event.size.width) + "x" + std::to_string(event.size.height));
		}

		if (event.type == sf::Event::LostFocus)
		{
			Debug::log(LogType::Verbose,"Window lost focus");
		}

		if (event.type == sf::Event::GainedFocus)
		{
			Debug::log(LogType::Verbose,"Window gained focus");
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::F)
			Debug::toggleFps();

		if (event.type == sf::Event::JoystickConnected ||
			event.type == sf::Event::JoystickDisconnected ||
			event.type == sf::Event::JoystickMoved ||
			event.type == sf::Event::TouchMoved ||
			event.type == sf::Event::SensorChanged ||
			event.type == sf::Event::TextEntered ||
			event.type == sf::Event::MouseWheelScrolled ||
			event.type == sf::Event::MouseMoved ||
			event.type == sf::Event::MouseWheelMoved)
			continue;
	}
}
void Game::update(float deltaTime)
{
	Debug::update(deltaTime);

	m_scene.update(deltaTime);
}
void Game::render(sf::RenderWindow &window, sf::RenderStates states)
{
	window.clear();

	m_scene.render(window, states);

	Debug::render(window, states);

	window.display();

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