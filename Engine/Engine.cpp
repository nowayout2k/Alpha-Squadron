//
// Created by Johnnie Otis on 6/13/24.
//

#include <SFML/Window/Event.hpp>
#include "Engine.h"
#include "State.h"
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"
#include "SettingsState.h"

#define FRAME_RATE_LIMIT 60.0f
#define TIME_STEP_MAX 1.0f/FRAME_RATE_LIMIT

Engine::Engine() : m_isPaused(false), m_stateStack(State::Context(m_window, m_input))
{
	createWindow(sf::VideoMode(1740,1000), "Alpha Squadron", sf::Style::Resize);
	registerStates();
	m_stateStack.pushState(StateId::Title);
}

void Engine::run()
{
	Debug::init();
	sf::Clock clock;
	float timeStep = 0;

	while (m_window.isOpen())
	{
		timeStep += clock.restart().asSeconds();
		while (timeStep > TIME_STEP_MAX)
		{
			timeStep -= TIME_STEP_MAX;
			processEvents();
			if(!m_isPaused)
				update(TIME_STEP_MAX);
		}
		render();
	}
}

void Engine::update(float deltaTime)
{
	Debug::update(deltaTime);
	m_stateStack.update(deltaTime);
}
void Engine::render()
{
	sf::RenderStates states;
	m_window.clear();
	m_stateStack.render(states);
	Debug::render(m_window, states);
	m_window.display();
}

void Engine::createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style)
{
	m_window.create(mode, title, style);
	m_window.setFramerateLimit(FRAME_RATE_LIMIT);
	m_window.setPosition(sf::Vector2i(0,0));
	m_window.setMouseCursorVisible(false);
	m_window.setVerticalSyncEnabled(false);
	m_window.setActive(true);
}
double eventCount = 0;
double frame = 0;
void Engine::processEvents()
{
	sf::Event event;
	Debug::log("FRAME: " + std::to_string(++frame));
	eventCount=0;
	while (m_window.pollEvent(event))
	{
		Debug::log("EVENT NUMBER" + std::to_string(eventCount++));
		m_stateStack.handleEvent(event);

		if (event.type == sf::Event::Closed || m_stateStack.isEmpty() || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)
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
}

void Engine::registerStates()
{
	m_stateStack.registerState<TitleState>(StateId::Title);
	m_stateStack.registerState<MenuState>(StateId::Menu);
	m_stateStack.registerState<GameState>(StateId::Game);
	m_stateStack.registerState<PauseState>(StateId::Pause);
	m_stateStack.registerState<SettingsState>(StateId::Settings);
}
