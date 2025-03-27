// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file TitleState.h
 * @brief Declaration of the TitleState class.
 *
 * This header declares the TitleState class, which represents the title screen of the game.
 * The state displays a background, company logo, and a blinking "Press Any Key To Continue!" prompt.
 * It transitions to the menu state upon key press.
 */

#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "State.h"

/**
 * @class TitleState
 * @brief Manages the title screen state.
 *
 * The TitleState class handles rendering the title screen graphics, updating a text
 * blinking effect, and processing input events to transition to the menu state.
 */
class TitleState : public State
{
 public:
	/**
	 * @brief Constructs a TitleState.
	 * @param stack The state stack.
	 * @param context The shared context with common resources.
	 */
	TitleState(StateStack& stack, Context context);

	/**
	 * @brief Renders the title screen.
	 */
	void render() override;

	/**
	 * @brief Updates the title screen state.
	 * @param deltaTime Time elapsed since the last update.
	 * @return True if the state should continue updating.
	 */
	bool update(sf::Time deltaTime) override;

	/**
	 * @brief Handles input events.
	 * @param event The SFML event to process.
	 * @return True if the event was handled.
	 */
	bool handleEvent(const sf::Event& event) override;

 private:
	sf::Sprite m_backgroundSprite; ///< Background sprite covering the title screen.
	sf::Sprite m_logoSprite;       ///< Sprite displaying the company logo.
	sf::Text m_continueText;       ///< Blinking text prompt instructing the user to continue.

	bool m_showText;             ///< Flag to toggle the visibility of the continue text.
	float m_textEffectTime;      ///< Accumulated time to manage blinking effect.
};

#endif //TITLESTATE_H_
