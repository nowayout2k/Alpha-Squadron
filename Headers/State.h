// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file State.h
 * @brief Declaration of the abstract State class.
 *
 * This header defines the State class, which serves as the base class for all game states.
 * States are managed by the StateStack and provide interfaces for rendering, updating,
 * and handling events. The Context structure bundles common resources required by states.
 */

#ifndef STATE_H_
#define STATE_H_

#include "StateIdentifiers.h"
#include "Player.h"

namespace Engine
{
	class StateStack;

	/**
	 * @class State
	 * @brief Abstract base class for game states.
	 *
	 * The State class defines the common interface for all states managed by the StateStack.
	 * Each state must implement render(), update(), and handleEvent() methods.
	 * States have access to shared resources via the Context structure.
	 */
	class State
	{
	 public:
		/// Smart pointer type for State objects.
		typedef std::unique_ptr<State> Ptr;

		/**
		 * @struct Context
		 * @brief Contains common resources shared among states.
		 *
		 * The Context structure bundles together the render window, audio system,
		 * and key binding configurations for both players.
		 */
		struct Context
		{
			/**
			 * @brief Constructs a Context.
			 * @param window Reference to the render window.
			 * @param audio Reference to the audio system.
			 * @param keys1 Reference to the key binding for player 1.
			 * @param keys2 Reference to the key binding for player 2.
			 */
			Context(sf::RenderWindow& window, Audio& audio, KeyBinding& keys1, KeyBinding& keys2)
				: Window(&window), Audio(&audio), KeysPlayer1(&keys1), KeysPlayer2(&keys2)
			{
			}
			sf::RenderWindow* Window; ///< Pointer to the render window.
			Audio* Audio;             ///< Pointer to the audio system.
			KeyBinding* KeysPlayer1;  ///< Pointer to the key binding for player 1.
			KeyBinding* KeysPlayer2;  ///< Pointer to the key binding for player 2.
		};

	 public:
		/**
		 * @brief Constructs a State.
		 * @param stack Reference to the StateStack that manages this state.
		 * @param context Shared context containing common resources.
		 */
		State(StateStack& stack, Context context) : m_stack(&stack), m_context(context)
		{
		}

		/// Virtual destructor.
		virtual ~State() = default;

		/// Renders the state. Must be implemented by derived classes.
		virtual void render() = 0;
		/**
		 * @brief Updates the state.
		 * @param deltaTime The time elapsed since the last update.
		 * @return True if the state should continue updating.
		 */
		virtual bool update(sf::Time deltaTime) = 0;
		/**
		 * @brief Handles an SFML event.
		 * @param event The event to handle.
		 * @return True if the event was handled.
		 */
		virtual bool handleEvent(const sf::Event& event) = 0;

	 protected:
		/**
		 * @brief Requests the state stack to push a new state.
		 * @param stateId Identifier of the state to push.
		 */
		void requestStackPush(AlphaSquadron::StateId stateId);
		/**
		 * @brief Requests the state stack to pop the current state.
		 */
		void requestStackPop();
		/**
		 * @brief Requests the state stack to clear all states.
		 */
		void requestStateClear();
		/**
		 * @brief Returns the shared context.
		 * @return The Context structure containing common resources.
		 */
		Context getContext() const
		{
			return m_context;
		}

	 private:
		StateStack* m_stack; ///< Pointer to the state stack managing this state.
		Context m_context;   ///< Shared context with common game resources.
	};
}

#endif //STATE_H_
