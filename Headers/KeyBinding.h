// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON_SOURCE_KEYBINDING_H_
#define ALPHA_SQUADRON_SOURCE_KEYBINDING_H_

#include <SFML/Window/Keyboard.hpp>
#include <map>
#include <vector>

/**
 * @file KeyBinding.h
 * @brief Declaration of the KeyBinding class.
 *
 * The KeyBinding class manages key assignments for local player actions.
 * It allows for assigning keys to actions, retrieving the assigned key,
 * checking for realtime actions, and obtaining all currently active realtime actions.
 * The file also declares the function IsRealtimeAction to determine if an action is realtime.
 */
namespace LocalPlayerAction
{
	/**
	 * @brief Enumeration of local player action types.
	 */
	enum ActionType
	{
		AccelerateNegX, ///< Accelerate in the negative X direction.
		AcceleratePosX, ///< Accelerate in the positive X direction.
		AccelerateNegY, ///< Accelerate in the negative Y direction.
		AcceleratePosY, ///< Accelerate in the positive Y direction.
		Fire,           ///< Fire weapon.
		LaunchMissile,  ///< Launch a missile.
		ActionCount     ///< Total number of actions.
	};
}

/**
 * @brief The KeyBinding class handles key mappings for local player actions.
 *
 * It supports assigning keys to actions, checking if a key corresponds to an action,
 * and retrieving all realtime actions that are currently active.
 */
class KeyBinding
{
 public:
	/// Type alias for action types.
	typedef LocalPlayerAction::ActionType ActionType;

	/**
	 * @brief Constructs a KeyBinding object with a given control preconfiguration.
	 * @param controlPreconfiguration The control scheme identifier (e.g., 1 for player 1, 2 for player 2).
	 */
	explicit KeyBinding(int controlPreconfiguration);

	/**
	 * @brief Assigns a key to a specific action.
	 * @param action The action to assign.
	 * @param key The key to assign to the action.
	 */
	void assignKey(ActionType action, sf::Keyboard::Key key);

	/**
	 * @brief Gets the key assigned to a specific action.
	 * @param action The action whose key is to be retrieved.
	 * @return The assigned key, or sf::Keyboard::Unknown if not found.
	 */
	sf::Keyboard::Key getAssignedKey(ActionType action) const;

	/**
	 * @brief Checks if a given key corresponds to an action.
	 * @param key The key to check.
	 * @param out The action associated with the key, if any.
	 * @return True if the key is bound to an action; false otherwise.
	 */
	bool checkAction(sf::Keyboard::Key key, ActionType& out) const;

	/**
	 * @brief Retrieves all realtime actions that are currently active.
	 * @return A vector of active action types.
	 */
	std::vector<ActionType> getRealtimeActions() const;

 private:
	/**
	 * @brief Initializes the default key bindings.
	 *
	 * This function sets up the initial key mappings for a given control preconfiguration.
	 */
	void initializeActions();

 private:
	std::map<sf::Keyboard::Key, ActionType> m_keyMap; ///< Mapping from keys to actions.
};

/**
 * @brief Determines if an action is a realtime action.
 * @param action The action to check.
 * @return True if the action is realtime; false otherwise.
 */
bool IsRealtimeAction(LocalPlayerAction::ActionType action);

#endif // ALPHA_SQUADRON_SOURCE_KEYBINDING_H_
