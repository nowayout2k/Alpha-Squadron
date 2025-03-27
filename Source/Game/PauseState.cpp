// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file PauseState.cpp
 * @brief Implements the PauseState class methods.
 *
 * This source file defines the functionality for the pause state,
 * including UI setup, event handling, and rendering the pause menu.
 */

#include "../../Headers/Game/PauseState.h"
#include "../../Headers/Engine/Button.h"

namespace AlphaSquadron
{
	PauseState::PauseState(Engine::StateStack& stack, Context context, bool letUpdatesThrough)
		: State(stack, context),
		  m_backgroundSprite(),
		  m_pausedText(),
		  m_guiContainer(*context.Audio),
		  m_letUpdatesThrough(letUpdatesThrough)
	{
		// Retrieve the font resource and window size.
		sf::Font& font = ResourceManager::loadResource(Engine::FontId::Arnold);
		sf::Vector2f windowSize(context.Window->getSize());

		// Configure the paused text.
		m_pausedText.setFont(font);
		m_pausedText.setString("Game Paused");
		m_pausedText.setCharacterSize(70);
		Engine::Utility::centerOrigin(m_pausedText);
		m_pausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

		// Create the "Return" button to resume the game.
		auto returnButton = std::make_shared<Engine::Button>(context);
		returnButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
		returnButton->setText(40, "Return");
		returnButton->setCallback([this]()
		{
		  requestStackPop();
		});

		// Create the "Back to menu" button to exit to the main menu.
		auto backToMenuButton = std::make_shared<Engine::Button>(context);
		backToMenuButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
		backToMenuButton->setText(40, "Back to menu");
		backToMenuButton->setCallback([this]()
		{
		  requestStateClear();
		  requestStackPush(StateId::Menu);
		});

		// Pack the buttons into the GUI container.
		m_guiContainer.pack(returnButton);
		m_guiContainer.pack(backToMenuButton);

		// Pause the background music when entering the pause state.
		getContext().Audio->pauseMusic(true);
	}

	PauseState::~PauseState()
	{
		// Resume music playback upon exiting the pause state.
		getContext().Audio->pauseMusic(false);
	}

	void PauseState::render()
	{
		// Set the default view for UI rendering.
		sf::RenderWindow& window = *getContext().Window;
		window.setView(window.getDefaultView());

		// Draw a semi-transparent black background overlay.
		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
		backgroundShape.setSize(sf::Vector2f(window.getSize()));
		window.draw(backgroundShape);

		// Draw the paused text and any instruction text.
		window.draw(m_pausedText);
		window.draw(m_instructionText);

		// Draw the GUI container holding the buttons.
		window.draw(m_guiContainer);
	}

	bool PauseState::update(sf::Time deltaTime)
	{
		// Allow updates to pass through if configured; otherwise, block underlying game updates.
		return m_letUpdatesThrough;
	}

	bool PauseState::handleEvent(const sf::Event& event)
	{
		// Forward the event to the GUI container for processing button interactions.
		m_guiContainer.handleEvent(event);
		return false;
	}
}