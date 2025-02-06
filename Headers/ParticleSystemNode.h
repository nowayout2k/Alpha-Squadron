// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON_HEADERS_PARTICLESYSTEMNODE_H_
#define ALPHA_SQUADRON_HEADERS_PARTICLESYSTEMNODE_H_

#include "World.h"
#include "Particle.h"

class ParticleSystemNode : public WorldNode
{
 public:
	explicit ParticleSystemNode(Particle::Type type);
	void addParticle(sf::Vector2f position);
	Particle::Type getParticleType() const { return m_type; };
	unsigned int getNodeType() const override { return WorldNode::getNodeType() | static_cast<unsigned int>(NodeType::ParticleSystem); }
	void update(sf::Time deltaTime, CommandQueue& commands) override;
	void render(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Rect<float> getBoundingRect() const override;
 protected:
	void loadResources() override;

 private:
	void computeVertices() const;
	void addVertex(float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const;
	std::deque<Particle> m_particles;
	const sf::Texture& m_texture;
	Particle::Type m_type;
	mutable sf::VertexArray m_vertexArray;
	mutable bool m_needsVertexUpdate;
};

#endif //ALPHA_SQUADRON_HEADERS_PARTICLESYSTEMNODE_H_
