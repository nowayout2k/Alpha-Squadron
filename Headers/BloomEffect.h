// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON_HEADERS_BLOOMEFFECT_H_
#define ALPHA_SQUADRON_HEADERS_BLOOMEFFECT_H_

#include "PostEffect.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <array>
namespace Engine
{
	/**
	 * @file BloomEffect.h
	 * @brief Declares the BloomEffect class for applying a bloom post-processing effect.
	 *
	 * The BloomEffect class applies a bloom effect to the input render texture using multiple passes.
	 * It uses brightness filtering, down sampling, and Gaussian blur to achieve the effect.
	 */
	class BloomEffect : public PostEffect
	{
	 public:
		/**
		 * @brief Default constructor.
		 */
		BloomEffect() = default;

		/**
		 * @brief Applies the bloom effect.
		 * @param input The input render texture.
		 * @param output The render target to output the final result.
		 */
		void apply(const sf::RenderTexture& input, sf::RenderTarget& output) override;

	 private:
		/**
		 * @brief Prepares the render textures used in the bloom effect.
		 * @param size The size of the input texture.
		 */
		void prepareTextures(sf::Vector2u size);

		/**
		 * @brief Filters bright areas from the input texture.
		 * @param input The input render texture.
		 * @param output The output render texture containing only bright areas.
		 */
		static void filterBright(const sf::RenderTexture& input, sf::RenderTexture& output);

		/**
		 * @brief Applies multiple blur passes to the render textures.
		 * @param renderTextures The array of render textures to be blurred.
		 */
		static void blurMultipass(std::array<sf::RenderTexture, 2>& renderTextures);

		/**
		 * @brief Applies a single blur pass.
		 * @param input The input render texture.
		 * @param output The output render texture.
		 * @param offsetFactor The offset factor used for the blur.
		 */
		static void blur(const sf::RenderTexture& input, sf::RenderTexture& output, sf::Vector2f offsetFactor);

		/**
		 * @brief Down samples the input texture to a lower resolution.
		 * @param input The input render texture.
		 * @param output The output render texture.
		 */
		static void downSample(const sf::RenderTexture& input, sf::RenderTexture& output);

		/**
		 * @brief Adds the source texture and the bloom texture together.
		 * @param source The original source render texture.
		 * @param bloom The bloom render texture.
		 * @param output The final output render target.
		 */
		static void add(const sf::RenderTexture& source, const sf::RenderTexture& bloom, sf::RenderTarget& output);

		typedef std::array<sf::RenderTexture, 2> RenderTextureArray;

		sf::RenderTexture m_brightnessTexture;   ///< Render texture for brightness filtering.
		RenderTextureArray m_firstPassTextures;     ///< Render textures used for the first blur pass.
		RenderTextureArray m_secondPassTextures;    ///< Render textures used for the second blur pass.
	};
}
#endif // ALPHA_SQUADRON_HEADERS_BLOOMEFFECT_H_
