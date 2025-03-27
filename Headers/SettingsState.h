// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file SettingsState.h
 * @brief Declaration of the SettingsState class.
 *
 * This header defines the SettingsState class, which manages the settings menu.
 * In this state, players can rebind keys for their actions. The state displays a background,
 * binding buttons, and labels that show the current key assignments.
 */

#ifndef SETTINGSSTATE_H_
#define SETTINGSSTATE_H_

#include "State.h"
#include "Player.h"
#include "Container.h"
#include "Button.h"
#include "Label.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <array>

/**
 * @class SettingsState
 * @brief Manages the key binding and settings menu.
 *
 * This state displays GUI elements to allow players to change key bindings for various actions.
 * It shows a background sprite, buttons for key binding, and labels for displaying the current assignments.
 */
class SettingsState : public State
{
 public:
	/**
	 * @brief Constructs a SettingsState.
	 * @param stack The state stack.
	 * @param context The game context, providing access to window, resources, and key bindings.
	 */
	explicit SettingsState(StateStack& stack, Context context);

	/**
	 * @brief Renders the settings menu.
	 */
	virtual void render() override;

	/**
	 * @brief Updates the settings state.
	 * @param deltaTime The elapsed time since the last update.
	 * @return True if the state should continue updating.
	 */
	virtual bool update(sf::Time deltaTime) override;

	/**
	 * @brief Handles SFML events.
	 * @param event The event to handle.
	 * @return True if the event was handled.
	 */
	virtual bool handleEvent(const sf::Event& event) override;

 private:
	/**
	 * @brief Updates the key binding labels to reflect current assignments.
	 */
	void updateLabels();

	/**
	 * @brief Adds a button and label pair for a key binding.
	 * @param index The action index for key binding.
	 * @param offset The vector offset to determine player (first or second).
	 * @param text The text to display on the button.
	 * @param context The game context.
	 */
	void addButtonLabel(std::size_t index, sf::Vector2i offset, const std::string& text, Context context);

	sf::Sprite m_backgroundSprite;   ///< Background sprite for the settings menu.
	GUI::Container m_guiContainer;     ///< Container for GUI elements (buttons and labels).
	// Arrays for key binding buttons and labels; there are two sets for two players.
	std::array<GUI::Button::Ptr, 2 * Player::ActionType::ActionCount> m_bindingButtons;
	std::array<GUI::Label::Ptr, 2 * Player::ActionType::ActionCount> m_bindingLabels;
};

#endif //SETTINGSSTATE_H_
