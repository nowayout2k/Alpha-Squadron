// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file ParticleSystemNode.cpp
 * @brief Implements the ParticleSystemNode class methods.
 *
 * This source file provides the implementation for managing and rendering a particle
 * system. It updates particle lifetimes, computes vertex data for rendering, and handles
 * particle addition.
 */

#include "../Headers/ParticleSystemNode.h"

ParticleSystemNode::ParticleSystemNode(Particle::Type type)
	: m_particles(),
	  m_texture(ResourceManager::loadResource(TextureId::Particle)),
	  m_type(type), m_vertexArray(sf::Quads), m_needsVertexUpdate(true)
{
	// Constructor initializes particle deque, texture reference, particle type,
	// vertex array (set to use quads), and marks vertices for update.
}

void ParticleSystemNode::addParticle(sf::Vector2f position)
{
	// Create a new particle with initial properties from game data.
	Particle particle;
	particle.Position = position;
	particle.Color = World::GameData.ParticleData[m_type].Color;
	particle.Lifetime = World::GameData.ParticleData[m_type].Lifetime;
	m_particles.push_back(particle);
}

void ParticleSystemNode::update(sf::Time deltaTime, CommandQueue& commands)
{
	// Remove particles that have expired.
	while (!m_particles.empty() && m_particles.front().Lifetime <= sf::Time::Zero)
		m_particles.pop_front();

	// Decrease the lifetime of each remaining particle.
	for (Particle& particle : m_particles)
		particle.Lifetime -= deltaTime;

	// Mark vertex array for update as particle states have changed.
	m_needsVertexUpdate = true;
}

void ParticleSystemNode::render(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Recompute vertices if particle data has changed.
	if (m_needsVertexUpdate)
	{
		computeVertices();
		m_needsVertexUpdate = false;
	}
	// Set the texture and draw the vertex array.
	states.texture = &m_texture;
	target.draw(m_vertexArray, states);
}

void ParticleSystemNode::computeVertices() const
{
	// Determine the size and half-size of the particle texture.
	sf::Vector2f size(m_texture.getSize());
	sf::Vector2f half = size / 2.f;
	m_vertexArray.clear();

	// For each particle, compute its quad vertices based on position and lifetime.
	for (const Particle& particle : m_particles)
	{
		sf::Vector2f pos = particle.Position;
		sf::Color c = particle.Color;
		// Compute transparency based on remaining lifetime.
		float ratio = particle.Lifetime.asSeconds() / World::GameData.ParticleData[m_type].Lifetime.asSeconds();
		c.a = static_cast<sf::Uint8>(255 * std::max(ratio, 0.f));
		// Add four vertices to form a quad.
		addVertex(pos.x - half.x, pos.y - half.y, 0.f, 0.f, c);
		addVertex(pos.x + half.x, pos.y - half.y, size.x, 0.f, c);
		addVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, c);
		addVertex(pos.x - half.x, pos.y + half.y, 0.f, size.y, c);
	}
}

void ParticleSystemNode::addVertex(float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const
{
	// Create a vertex with the specified position, texture coordinate, and color.
	sf::Vertex vertex;
	vertex.position = sf::Vector2f(worldX, worldY);
	vertex.texCoords = sf::Vector2f(texCoordX, texCoordY);
	vertex.color = color;
	// Append the vertex to the vertex array.
	m_vertexArray.append(vertex);
}

sf::Rect<float> ParticleSystemNode::getBoundingRect() const
{
	// Return an empty rectangle; bounding rectangle is not used for particle systems.
	return {};
}

void ParticleSystemNode::loadResources()
{
	// Resource loading is handled externally; no implementation needed here.
}
