// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "State.h"
#include "World.h"
#include "Player.h"

namespace AlphaSquadron
{
	/**
	 * @file GameState.h
	 * @brief Declaration of the GameState class.
	 *
	 * The GameState class manages the main game simulation. It contains a World object
	 * that represents the game world and a Player object that handles player input and status.
	 * The state updates the world, processes input, and transitions to GameOver or MissionSuccess states
	 * based on the game conditions.
	 */
	class GameState : public Engine::State
	{
	 public:
		/**
		 * @brief Constructs a GameState.
		 * @param stack The state stack.
		 * @param context The shared state context.
		 */
		GameState(Engine::StateStack& stack, State::Context context);

		/**
		 * @brief Renders the game state.
		 */
		void render() override;

		/**
		 * @brief Updates the game state.
		 * @param deltaTime The time elapsed since the last update.
		 * @return True if the state should continue, false otherwise.
		 */
		bool update(sf::Time deltaTime) override;

		/**
		 * @brief Handles an incoming event.
		 * @param event The event to process.
		 * @return True if the event was handled.
		 */
		bool handleEvent(const sf::Event& event) override;

	 private:
		World m_world;    ///< The game world.
		Player m_player;  ///< The player.
	};
}
#endif // GAMESTATE_H_
