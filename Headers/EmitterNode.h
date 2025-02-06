//
// Created by Johnnie on 2/5/2025.
//

#ifndef ALPHA_SQUADRON_HEADERS_EMITTERNODE_H_
#define ALPHA_SQUADRON_HEADERS_EMITTERNODE_H_

#include "Particle.h"
#include "WorldNode.h"
#include "ParticleNode.h"

class EmitterNode : public WorldNode
{
 public:
	explicit EmitterNode(Particle::Type type);
 protected:
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;
	void update(sf::Time deltaTime, CommandQueue& commands) override;

 private:
	sf::Time m_accumulatedTime;
	Particle::Type m_type;
	ParticleNode* m_particleSystem;
};

#endif //ALPHA_SQUADRON_HEADERS_EMITTERNODE_H_
