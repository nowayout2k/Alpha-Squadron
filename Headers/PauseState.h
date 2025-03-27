// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file PauseState.h
 * @brief Declaration of the PauseState class.
 *
 * This header declares the PauseState class, which represents the pause state in the game.
 * It handles rendering the pause menu, processing user input, and optionally allowing game updates while paused.
 */

#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_

#include "State.h"
#include "Container.h"

/**
 * @class PauseState
 * @brief Manages the game's pause state.
 *
 * The PauseState class displays the pause menu and handles user input for resuming the game or returning to the menu.
 */
class PauseState : public State
{
 public:
	/**
	 * @brief Constructs a PauseState.
	 * @param stack Reference to the state stack.
	 * @param context Game context providing resources, window, and audio.
	 * @param letUpdatesThrough If true, allows underlying game updates while paused.
	 */
	PauseState(StateStack& stack, Context context, bool letUpdatesThrough = false);

	/**
	 * @brief Destructor.
	 *
	 * Resumes music playback when the pause state is destroyed.
	 */
	~PauseState();

	/**
	 * @brief Renders the pause screen and UI elements.
	 */
	virtual void render() override;

	/**
	 * @brief Updates the pause state.
	 * @param deltaTime Time elapsed since the last update.
	 * @return True if the state should continue updating.
	 */
	virtual bool update(sf::Time deltaTime) override;

	/**
	 * @brief Handles user input events.
	 * @param event The event to process.
	 * @return True if the event was handled.
	 */
	virtual bool handleEvent(const sf::Event& event) override;

 private:
	sf::Text m_pausedText;           ///< Text displayed to indicate the game is paused.
	sf::Text m_instructionText;      ///< Text displaying additional instructions (if any).
	sf::Sprite m_backgroundSprite;   ///< Background sprite for the pause screen.
	GUI::Container m_guiContainer;   ///< Container holding GUI elements (buttons).
	bool m_letUpdatesThrough;        ///< Flag indicating whether updates should continue in the background.
};

#endif //PAUSESTATE_H_
