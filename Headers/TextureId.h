// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file TextureId.h
 * @brief Declaration of the TextureId enumeration.
 *
 * This header defines the TextureId enumeration, which lists identifiers for the various
 * textures used in the game. These identifiers are used to load and manage textures for backgrounds,
 * sprite sheets, UI elements, particle effects, and other graphical assets.
 */

#ifndef TEXTUREID_H_
#define TEXTUREID_H_

/**
 * @enum TextureId
 * @brief Enumerates texture identifiers.
 *
 * This enumeration provides unique identifiers for each texture resource in the game.
 * It includes various background textures, sprite sheets for game characters and UI elements,
 * as well as textures for special effects.
 */
enum class TextureId
{
	ForestBg,            ///< Texture for a forest background.
	SkyBg,               ///< Texture for a sky background.
	JungleBg,            ///< Texture for a jungle background.
	TallCityBg,          ///< Texture for a tall city background.
	NightCityBg,         ///< Texture for a night city background.
	DecayedCityBg,       ///< Texture for a decayed city background.
	GameSpriteSheet,     ///< Sprite sheet containing game character graphics.
	UiSpriteSheet,       ///< Sprite sheet used for UI elements.
	ExplosionSpriteSheet,///< Sprite sheet for explosion effects.
	MetalBg,             ///< Texture for a metal background.
	Particle,            ///< Texture for particle effects.
	CompanyLogo,         ///< Texture for the company logo.
	TextureCount         ///< Total number of texture identifiers.
};

#endif //TEXTUREID_H_
