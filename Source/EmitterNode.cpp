// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/EmitterNode.h"

EmitterNode::EmitterNode(Particle::Type type) : m_type(type)
{

}

void EmitterNode::render(sf::RenderTarget& renderTarget, sf::RenderStates states) const
{

}

void EmitterNode::update(sf::Time deltaTime, CommandQueue& commands)
{
	if (m_particleSystem)
	{
		emitParticles(deltaTime);
	}
	else
	{
		auto finder = [this] (ParticleSystemNode& container, sf::Time)
		{
		  if (container.getParticleType() == m_type)
			  m_particleSystem = &container;
		};
		Command command;
		command.NodeType = static_cast<unsigned int>(NodeType::ParticleSystem);
		command.Action = DerivedAction<ParticleSystemNode>(finder);
		commands.push(command);
	}
}

void EmitterNode::emitParticles(sf::Time dt)
{
	const float emissionRate = 30.f;
	const sf::Time interval = sf::seconds(1.f) / emissionRate;
	m_accumulatedTime += dt;
	while (m_accumulatedTime > interval)
	{
		m_accumulatedTime -= interval;
		m_particleSystem->addParticle(getWorldPosition());
	}
}
sf::Rect<float> EmitterNode::getBoundingRect() const
{
	return {};
}
void EmitterNode::loadResources()
{

}
