// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include <SFML/Window/Event.hpp>
#include "../../Headers/Engine/Engine.h"
#include "../../Headers/Game/TitleState.h"
#include "../../Headers/Game/MenuState.h"
#include "../../Headers/Game/GameState.h"
#include "../../Headers/Game/PauseState.h"
#include "../../Headers/Game/SettingsState.h"
#include "../../Headers/Game/GameOverState.h"
#include "../../Headers/Game/MultiplayerGameState.h"

#define FRAME_RATE_LIMIT 60.0f
#define TIME_STEP_MAX (1.0f / FRAME_RATE_LIMIT)

namespace Engine
{
	GameEngine::GameEngine()
		: m_isPaused(false),
		  m_keyBinding1(1),
		  m_keyBinding2(2),
		  m_stateStack(State::Context(m_window, m_audio, m_keyBinding1, m_keyBinding2))
	{
		createWindow(sf::VideoMode(2000, 1000), "Alpha Squadron", sf::Style::Resize);
		registerStates();
		m_stateStack.pushState(AlphaSquadron::StateId::Title);
	}

	void GameEngine::run()
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
				if (!m_isPaused)
					update(sf::seconds(TIME_STEP_MAX));
			}
			render();
		}
	}

	void GameEngine::update(sf::Time deltaTime)
	{
		m_stateStack.update(deltaTime);
	}

	void GameEngine::render()
	{
		sf::RenderStates states;
		m_window.clear();
		m_stateStack.render();
		m_window.display();
	}

	void GameEngine::createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style)
	{
		m_window.create(mode, title, style);
		m_window.setFramerateLimit(FRAME_RATE_LIMIT);
		m_window.setPosition(sf::Vector2i(0, 0));
		m_window.setMouseCursorVisible(false);
		m_window.setVerticalSyncEnabled(false);
		m_window.setActive(true);
	}

	void GameEngine::processEvents()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			m_stateStack.handleEvent(event);

			if (event.type == sf::Event::Closed || m_stateStack.isEmpty() ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				m_window.close();
			}

			if (event.type == sf::Event::LostFocus)
			{
				Engine::Debug::log("Window lost focus");
				m_isPaused = true;
			}

			if (event.type == sf::Event::GainedFocus)
			{
				Engine::Debug::log("Window gained focus");
				m_isPaused = false;
			}
		}
	}

	void GameEngine::registerStates()
	{
		m_stateStack.registerState<AlphaSquadron::TitleState>(AlphaSquadron::StateId::Title);
		m_stateStack.registerState<AlphaSquadron::MenuState>(AlphaSquadron::StateId::Menu);
		m_stateStack.registerState<AlphaSquadron::GameState>(AlphaSquadron::StateId::Game);
		m_stateStack.registerState<AlphaSquadron::MultiplayerGameState>(AlphaSquadron::StateId::HostGame, true);
		m_stateStack.registerState<AlphaSquadron::MultiplayerGameState>(AlphaSquadron::StateId::JoinGame, false);
		m_stateStack.registerState<AlphaSquadron::PauseState>(AlphaSquadron::StateId::NetworkPause, true);
		m_stateStack.registerState<AlphaSquadron::PauseState>(AlphaSquadron::StateId::Pause);
		m_stateStack.registerState<AlphaSquadron::SettingsState>(AlphaSquadron::StateId::Settings);
		m_stateStack.registerState<AlphaSquadron::GameOverState>(AlphaSquadron::StateId::GameOver, "Mission Failed!");
		m_stateStack.registerState<AlphaSquadron::GameOverState>(AlphaSquadron::StateId::MissionSuccess, "Mission Successful!");
	}
}