// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef GAMEOVERSTATE_H_
#define GAMEOVERSTATE_H_

#include "StateStack.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

namespace AlphaSquadron
{
	/**
	 * @file GameOverState.h
	 * @brief Declaration of the GameOverState class.
	 *
	 * The GameOverState class represents the state displayed when the game is over.
	 * It shows a game over message, waits for a fixed duration, and then transitions to the menu state.
	 */
	class GameOverState : public Engine::State
	{
	 public:
		/**
		 * @brief Constructs a GameOverState.
		 * @param stack Reference to the state stack.
		 * @param context Context providing access to shared resources.
		 * @param text The game over message to display.
		 */
		GameOverState(Engine::StateStack& stack, Context context, const std::string& text);

		/**
		 * @brief Renders the game over state.
		 */
		virtual void render() override;

		/**
		 * @brief Updates the game over state.
		 * @param dt Time elapsed since the last update.
		 * @return False, as this state does not require further updates.
		 */
		virtual bool update(sf::Time dt) override;

		/**
		 * @brief Handles events while in the game over state.
		 * @param event The event to handle.
		 * @return False, as events do not affect this state.
		 */
		virtual bool handleEvent(const sf::Event& event) override;

	 private:
		sf::Text m_gameOverText; ///< Text element displaying the game over message.
		float m_elapsedTime;     ///< Accumulated time since the state was entered.
	};
}

#endif // GAMEOVERSTATE_H_
