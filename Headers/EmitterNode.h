// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON_HEADERS_EMITTERNODE_H_
#define ALPHA_SQUADRON_HEADERS_EMITTERNODE_H_

#include "Particle.h"
#include "WorldNode.h"
#include "ParticleSystemNode.h"

class EmitterNode : public WorldNode
{
 public:
	explicit EmitterNode(Particle::Type type);
	sf::Rect<float> getBoundingRect() const override;
 protected:
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;
	void update(sf::Time deltaTime, CommandQueue& commands) override;
	void loadResources() override;

 private:
	void emitParticles(sf::Time dt);
	sf::Time m_accumulatedTime;
	Particle::Type m_type;
	ParticleSystemNode* m_particleSystem{};
};

#endif //ALPHA_SQUADRON_HEADERS_EMITTERNODE_H_
