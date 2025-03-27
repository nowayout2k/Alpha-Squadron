// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ENGINE_H_
#define ENGINE_H_

#include "World.h"
#include "Player.h"
#include "StateStack.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <string>

/**
 * @file Engine.h
 * @brief Declaration of the Engine class.
 *
 * The Engine class manages the main game loop, window creation, event processing,
 * updating and rendering of the game states, as well as registering the game states.
 */
namespace Engine
{
	class GameEngine
	{
	 public:
		/**
		 * Constructs the Engine.
		 */
		GameEngine();

		/**
		 * Updates the game state.
		 * @param deltaTime The time elapsed since the last update.
		 */
		void update(sf::Time deltaTime);

		/**
		 * Renders the current game state.
		 */
		void render();

		/**
		 * Processes input events.
		 */
		void processEvents();

		/**
		 * Runs the main game loop.
		 */
		void run();

		/**
		 * Registers all game states.
		 */
		void registerStates();

	 private:
		/**
		 * Creates the game window.
		 * @param mode The video mode for the window.
		 * @param title The title of the window.
		 * @param style The window style.
		 */
		void createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);

		bool m_isPaused;                ///< Flag indicating if the game is paused.
		sf::RenderWindow m_window;      ///< The main render window.
		Audio m_audio;                  ///< The audio system.
		StateStack m_stateStack;        ///< The stack of game states.
		KeyBinding m_keyBinding1;       ///< First key binding configuration.
		KeyBinding m_keyBinding2;       ///< Second key binding configuration.
	};
}
#endif // ENGINE_H_
