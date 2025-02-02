// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include <SFML/Window/Event.hpp>
#include "../Headers/Engine.h"
#include "../Headers/State.h"
#include "../Headers/TitleState.h"
#include "../Headers/MenuState.h"
#include "../Headers/GameState.h"
#include "../Headers/PauseState.h"
#include "../Headers/SettingsState.h"
#include "../Headers/GameOverState.h"

#define FRAME_RATE_LIMIT 60.0f
#define TIME_STEP_MAX 1.0f/FRAME_RATE_LIMIT

sf::RenderWindow Engine::m_window = {};

Engine::Engine() : m_isPaused(false), m_stateStack(State::Context(m_window, m_input))
{
	createWindow(sf::VideoMode(2000,1000), "Alpha Squadron", sf::Style::Resize);
	registerStates();
	m_stateStack.pushState(StateId::Title);
}

void Engine::run()
{
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
	m_stateStack.update(deltaTime);
}
void Engine::render()
{
	sf::RenderStates states;
	m_window.clear();
	m_stateStack.render(states);
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

void Engine::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
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
	m_stateStack.registerState<GameOverState>(StateId::GameOver);
}
