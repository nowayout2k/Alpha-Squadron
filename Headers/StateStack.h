// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file StateStack.h
 * @brief Declaration of the StateStack class.
 *
 * The StateStack class manages a stack of game states (derived from State) and
 * processes pending changes (push, pop, clear) to the state stack. It also
 * provides mechanisms for state registration, event handling, updating, and rendering.
 */

#ifndef STATESTACK_H_
#define STATESTACK_H_

#include <SFML/Graphics.hpp>
#include <unordered_set>
#include "State.h"

/**
 * @class StateStack
 * @brief Manages a stack of states and state transitions.
 *
 * The StateStack is responsible for updating, rendering, and handling events for
 * active states. It supports state registration via factory functions and defers
 * state changes until the end of the current update cycle.
 */
class StateStack
{
 public:
	/**
	 * @enum StackActionType
	 * @brief Specifies the type of pending state change.
	 */
	enum StackActionType
	{
		Push,  ///< Push a new state onto the stack.
		Pop,   ///< Pop the current state off the stack.
		Clear, ///< Clear all states.
	};

	/**
	 * @brief Registers a state with the state stack using its factory function.
	 * @tparam T The state class to register.
	 * @param stateId The identifier for the state.
	 */
	template<typename T>
	void registerState(StateId stateId)
	{
		m_factories[stateId] = [this]()
		{
		  return State::Ptr(new T(*this, m_context));
		};
	}

	/**
	 * @brief Registers a state with an additional parameter.
	 * @tparam T The state class to register.
	 * @tparam Param The type of the extra parameter.
	 * @param stateId The identifier for the state.
	 * @param arg The extra argument for the state constructor.
	 */
	template<typename T, typename Param>
	void registerState(StateId stateId, Param arg)
	{
		m_factories[stateId] = [this, arg]()
		{
		  return State::Ptr(new T(*this, m_context, arg));
		};
	}

	/**
	 * @brief Updates the active state(s) on the stack.
	 * @param deltaTime The elapsed time since the last update.
	 */
	void update(sf::Time deltaTime);

	/**
	 * @brief Renders all active states.
	 */
	void render();

	/**
	 * @brief Forwards an event to the active states.
	 * @param event The SFML event to process.
	 */
	void handleEvent(const sf::Event& event);

	/**
	 * @brief Requests to push a new state onto the stack.
	 * @param stateId The identifier of the state to push.
	 */
	void pushState(StateId stateId);

	/**
	 * @brief Requests to pop the current state.
	 */
	void popState();

	/**
	 * @brief Requests to clear all states from the stack.
	 */
	void clearStates();

	/**
	 * @brief Checks if the state stack is empty.
	 * @return True if no states are active, false otherwise.
	 */
	bool isEmpty() const;

	/**
	 * @brief Constructs a StateStack with a given context.
	 * @param context The shared context containing resources.
	 */
	explicit StateStack(State::Context context);
	~StateStack() = default;

 private:
	/**
	 * @struct PendingChange
	 * @brief Represents a pending change to the state stack.
	 *
	 * PendingChange is used internally to store state stack modifications
	 * (push, pop, clear) until they are applied.
	 */
	struct PendingChange
	{
		/**
		 * @brief Constructs a PendingChange with an action and state id.
		 * @param stackActionType The type of action.
		 * @param stateId The identifier of the state (if applicable).
		 */
		PendingChange(StackActionType stackActionType, StateId stateId) : StackActionType(stackActionType), StateId(stateId){};
		/**
		 * @brief Constructs a PendingChange with an action only.
		 * @param stackActionType The type of action.
		 */
		explicit PendingChange(StackActionType stackActionType) : StackActionType(stackActionType), StateId(StateId::None){};
		StackActionType StackActionType; ///< The type of stack action.
		StateId StateId;                 ///< The state identifier associated with the action.
	};

	// Copying is not allowed.
	StateStack(const StateStack&);
	StateStack& operator=(const StateStack&);

	/**
	 * @brief Applies all pending state changes.
	 */
	void applyPendingChanges();

	/**
	 * @brief Handles rollover key events to prevent multiple event triggers.
	 * @param event The event to process.
	 * @return True if the event was consumed as a rollover event.
	 */
	bool handleRolloverKeyEvent(const sf::Event& event);

	/**
	 * @brief Creates a state instance using its registered factory.
	 * @param stateId The identifier of the state to create.
	 * @return A smart pointer to the created state.
	 */
	State::Ptr createState(StateId stateId);

	std::vector<State::Ptr> m_stack;                          ///< Stack of active states.
	std::vector<PendingChange> m_pendingList;                 ///< List of pending state changes.
	State::Context m_context;                                 ///< Shared context for all states.
	std::map<StateId, std::function<State::Ptr()>> m_factories; ///< Factories for creating states.
	std::unordered_set<sf::Keyboard::Key> m_rolloverPressedKeys;///< Keys that are held down for rollover prevention.
	std::vector<sf::Keyboard::Key> m_allKeys;                 ///< List of all keyboard keys.
};

#endif //STATESTACK_H_
