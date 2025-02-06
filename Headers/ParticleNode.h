//
// Created by Johnnie on 2/5/2025.
//

#ifndef ALPHA_SQUADRON_HEADERS_PARTICLENODE_H_
#define ALPHA_SQUADRON_HEADERS_PARTICLENODE_H_

#include "World.h"
#include "Particle.h"

class ParticleNode : public WorldNode
{
 public:
	explicit ParticleNode(Particle::Type type);
	void addParticle(sf::Vector2f position);
	Particle::Type getParticleType() const { return m_type; };
	unsigned int getNodeType() const override { return WorldNode::getNodeType() | static_cast<unsigned int>(NodeType::Particle); }
	void update(sf::Time deltaTime, CommandQueue& commands) override;
	void render(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
	void computeVertices() const;
	void addVertex(float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const;
	std::deque<Particle> m_particles;
	const sf::Texture& m_texture;
	Particle::Type m_type;
	mutable sf::VertexArray m_vertexArray;
	mutable bool m_needsVertexUpdate;
};

#endif //ALPHA_SQUADRON_HEADERS_PARTICLENODE_H_
