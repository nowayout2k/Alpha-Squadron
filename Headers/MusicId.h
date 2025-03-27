// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file MusicId.h
 * @brief Declaration of the MusicId enumeration.
 *
 * This header defines the MusicId enumeration, which lists identifiers for
 * different music tracks in the game. These identifiers are used to select
 * and play the appropriate music track, such as during gameplay or in menus.
 */

#ifndef MUSICID_H_
#define MUSICID_H_

/**
 * @enum MusicId
 * @brief Enumerates music track identifiers.
 *
 * This enumeration is used to specify which music track should be played.
 */
enum class MusicId
{
	GameMusic, ///< Identifier for the game music track.
	MenuMusic, ///< Identifier for the menu music track.
};

#endif //MUSICID_H_
