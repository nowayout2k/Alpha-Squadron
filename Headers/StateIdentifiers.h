// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file StateIdentifiers.h
 * @brief Declaration of the StateId enumeration.
 *
 * This header defines the StateId enumeration which lists identifiers for the various
 * states in the game. These identifiers are used to manage transitions between game states
 * such as the title screen, main menu, gameplay, pause, game over, and network-related states.
 */

#ifndef STATEIDENTIFIERS_H_
#define STATEIDENTIFIERS_H_

namespace AlphaSquadron
{
	/**
	 * @enum StateId
	 * @brief Enumerates the different states in the game.
	 *
	 * The StateId enumeration provides unique identifiers for each state managed by the state stack.
	 * It includes states for title, menu, game, loading, settings, pause, game over, network pause,
	 * hosting, joining a game, and mission success.
	 */
	enum class StateId
	{
		None,         ///< No state.
		Title,        ///< Title screen state.
		Menu,         ///< Main menu state.
		Game,         ///< Gameplay state.
		Loading,      ///< Loading state.
		Settings,     ///< Settings menu state.
		Pause,        ///< Pause screen state.
		GameOver,     ///< Game over state.
		NetworkPause, ///< Network pause state.
		HostGame,     ///< State for hosting a game.
		JoinGame,     ///< State for joining a game.
		MissionSuccess///< Mission success state.
	};
}
#endif //STATEIDENTIFIERS_H_
