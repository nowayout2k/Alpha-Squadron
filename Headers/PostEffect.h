// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file PostEffect.h
 * @brief Declaration of the PostEffect class.
 *
 * This header declares the PostEffect abstract class, which defines an interface for
 * applying post-processing effects to a rendered scene. It provides a method for applying
 * a custom effect, checking shader support, and a helper to apply a shader.
 */

#ifndef ALPHA_SQUADRON_HEADERS_POSTEFFECT_H_
#define ALPHA_SQUADRON_HEADERS_POSTEFFECT_H_

#include <SFML/Graphics/RenderTexture.hpp>

class PostEffect
{
 public:
	/**
	 * @brief Virtual destructor.
	 */
	virtual ~PostEffect() = default;

	/**
	 * @brief Applies the post effect to the input render texture and outputs the result.
	 * @param input The render texture to process.
	 * @param output The render target where the processed image is drawn.
	 */
	virtual void apply(const sf::RenderTexture& input, sf::RenderTarget& output) = 0;

	/**
	 * @brief Checks if the system supports shaders.
	 * @return True if shaders are available; false otherwise.
	 */
	static bool isSupported();

 protected:
	/**
	 * @brief Helper function to apply a shader to the entire output render target.
	 * @param shader The shader to apply.
	 * @param output The render target to which the shader is applied.
	 */
	static void applyShader(const sf::Shader& shader, sf::RenderTarget& output);
};

#endif //ALPHA_SQUADRON_HEADERS_POSTEFFECT_H_
