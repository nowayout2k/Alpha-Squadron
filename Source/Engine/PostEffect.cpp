// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Shader.hpp>
#include "../../Headers/Engine/PostEffect.h"

namespace Engine
{
	void PostEffect::applyShader(const sf::Shader& shader, sf::RenderTarget& output)
	{
		// Retrieve the size of the output render target.
		sf::Vector2f outputSize = static_cast<sf::Vector2f>(output.getSize());

		// Create a vertex array using a triangle strip with 4 vertices to cover the entire target.
		sf::VertexArray vertices(sf::TrianglesStrip, 4);
		// Define vertices with positions and texture coordinates.
		vertices[0] = sf::Vertex(sf::Vector2f(0, 0), sf::Vector2f(0, 1));                 // Top-left vertex.
		vertices[1] = sf::Vertex(sf::Vector2f(outputSize.x, 0), sf::Vector2f(1, 1));        // Top-right vertex.
		vertices[2] = sf::Vertex(sf::Vector2f(0, outputSize.y), sf::Vector2f(0, 0));        // Bottom-left vertex.
		vertices[3] = sf::Vertex(sf::Vector2f(outputSize), sf::Vector2f(1, 0));             // Bottom-right vertex.

		// Setup render states with the shader and disable blending.
		sf::RenderStates states;
		states.shader = &shader;
		states.blendMode = sf::BlendNone;

		// Draw the vertex array using the specified shader.
		output.draw(vertices, states);
	}

	bool PostEffect::isSupported()
	{
		// Return whether SFML shaders are available on this system.
		return sf::Shader::isAvailable();
	}
}