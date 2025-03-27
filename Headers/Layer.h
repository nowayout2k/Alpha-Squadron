// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef LAYER_H_
#define LAYER_H_

/**
 * @file Layer.h
 * @brief Declaration of the Layer enumeration.
 *
 * The Layer enumeration defines rendering layers for game elements.
 * It is used to determine the order in which elements are drawn.
 */
enum class Layer
{
	Background = 0, // Background layer.
	UI = 1,         // User interface layer.
	SpriteBack = 2, // Back sprite layer.
	SpriteFront = 3, // Front sprite layer.
	Audio = 4,      // Audio layer.
	LayerCount = 5  // Total number of layers.
};

#endif // LAYER_H_
