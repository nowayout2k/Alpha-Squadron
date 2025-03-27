// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef MENUSTATE_H_
#define MENUSTATE_H_

// Local includes using quotes.
#include "StateStack.h"
#include "Container.h"

// SFML includes.
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

/**
 * @file MenuState.h
 * @brief Declaration of the MenuState class.
 *
 * The MenuState class represents the main menu state. It displays a background,
 * title text, and a container of GUI buttons that allow the player to start the game,
 * host or join multiplayer, access settings, or exit the game. It also plays menu music.
 */
class MenuState : public State
{
 public:
	/**
	 * @brief Constructs the MenuState.
	 * @param stack The state stack.
	 * @param context The shared state context.
	 */
	explicit MenuState(StateStack& stack, Context context);

	/**
	 * @brief Renders the menu state.
	 */
	void render() override;

	/**
	 * @brief Updates the menu state.
	 * @param deltaTime The time elapsed since the last update.
	 * @return True if the state should continue updating.
	 */
	bool update(sf::Time deltaTime) override;

	/**
	 * @brief Handles input events in the menu state.
	 * @param event The event to handle.
	 * @return True if the event was handled.
	 */
	bool handleEvent(const sf::Event& event) override;

 private:
	sf::Sprite m_backgroundSprite; ///< Background sprite for the menu.
	sf::Text m_titleText;          ///< Title text for the menu.
	GUI::Container m_guiContainer; ///< Container for menu buttons.
};

#endif // MENUSTATE_H_
