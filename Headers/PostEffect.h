// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON_HEADERS_POSTEFFECT_H_
#define ALPHA_SQUADRON_HEADERS_POSTEFFECT_H_

#include <SFML/Graphics/RenderTexture.hpp>
class PostEffect
{
 public:
	virtual ~PostEffect() = default;
	virtual void apply(const sf::RenderTexture& input, sf::RenderTarget& output) = 0;
	static bool isSupported();
 protected:
	static void applyShader(const sf::Shader& shader, sf::RenderTarget& output);
};

#endif //ALPHA_SQUADRON_HEADERS_POSTEFFECT_H_
