// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON_HEADERS_BLOOMEFFECT_H_
#define ALPHA_SQUADRON_HEADERS_BLOOMEFFECT_H_

#include "PostEffect.h"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <array>

class BloomEffect : public PostEffect
{
 public:
	BloomEffect() = default;
	void apply(const sf::RenderTexture& input, sf::RenderTarget& output) override;
 private:
	typedef std::array<sf::RenderTexture, 2> RenderTextureArray;

	void prepareTextures(sf::Vector2u size);
	static void filterBright(const sf::RenderTexture& input, sf::RenderTexture& output);
	static void blurMultipass(RenderTextureArray& renderTextures);
	static void blur(const sf::RenderTexture& input, sf::RenderTexture& output, sf::Vector2f offsetFactor);
	static void downSample(const sf::RenderTexture& input, sf::RenderTexture& output);
	static void add(const sf::RenderTexture& source, const sf::RenderTexture& bloom, sf::RenderTarget& output);

	sf::RenderTexture	m_brightnessTexture;
	RenderTextureArray	m_firstPassTextures;
	RenderTextureArray	m_secondPassTextures;
};

#endif //ALPHA_SQUADRON_HEADERS_BLOOMEFFECT_H_
