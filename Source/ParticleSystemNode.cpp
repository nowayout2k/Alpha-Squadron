// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/ParticleSystemNode.h"

ParticleSystemNode::ParticleSystemNode(Particle::Type type) : m_particles(),
															  m_texture(ResourceManager::loadResource(TextureId::Particle)),
															  m_type(type), m_vertexArray(sf::Quads), m_needsVertexUpdate(true)
{

}

void ParticleSystemNode::addParticle(sf::Vector2f position)
{
	Particle particle;
	particle.Position = position;
	particle.Color = World::GameData.ParticleData[m_type].Color;
	particle.Lifetime = World::GameData.ParticleData[m_type].Lifetime;
	m_particles.push_back(particle);
}

void ParticleSystemNode::update(sf::Time deltaTime, CommandQueue& commands)
{
	while (!m_particles.empty() && m_particles.front().Lifetime <= sf::Time::Zero)
		m_particles.pop_front();

	for(Particle& particle : m_particles)
		particle.Lifetime -= deltaTime;

	m_needsVertexUpdate = true;
}
void ParticleSystemNode::render(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_needsVertexUpdate)
	{
		computeVertices();
		m_needsVertexUpdate = false;
	}
	states.texture = &m_texture;
	target.draw(m_vertexArray, states);

}
void ParticleSystemNode::computeVertices() const
{
	sf::Vector2f size(m_texture.getSize());
	sf::Vector2f half = size / 2.f;
	m_vertexArray.clear();

	for(const Particle& particle : m_particles)
	{
		sf::Vector2f pos = particle.Position;
		sf::Color c = particle.Color;
		float ratio = particle.Lifetime.asSeconds() / World::GameData.ParticleData[m_type].Lifetime.asSeconds();
		c.a = static_cast<sf::Uint8>(255 * std::max(ratio, 0.f));
		addVertex(pos.x - half.x, pos.y - half.y, 0.f, 0.f, c);
		addVertex(pos.x + half.x, pos.y - half.y, size.x, 0.f, c);
		addVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, c);
		addVertex(pos.x - half.x, pos.y + half.y, 0.f, size.y, c);
	}
}

void ParticleSystemNode::addVertex(float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const
{
	sf::Vertex vertex;
	vertex.position = sf::Vector2f(worldX, worldY);
	vertex.texCoords = sf::Vector2f(texCoordX, texCoordY);
	vertex.color = color;
	m_vertexArray.append(vertex);
}

sf::Rect<float> ParticleSystemNode::getBoundingRect() const
{
	return {};
}

void ParticleSystemNode::loadResources()
{

}
