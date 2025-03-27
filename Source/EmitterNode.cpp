// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/EmitterNode.h"

namespace Engine
{
	EmitterNode::EmitterNode(AlphaSquadron::ParticleType type)
		: m_accumulatedTime(sf::Time::Zero), m_type(type), m_particleSystem(nullptr)
	{
	}

	void EmitterNode::render(sf::RenderTarget& renderTarget, sf::RenderStates states) const
	{
		// The emitter does not render anything.
	}

	void EmitterNode::update(sf::Time deltaTime, CommandQueue& commands)
	{
		if (m_particleSystem)
		{
			emitParticles(deltaTime);
		}
		else
		{
			auto finder = [this](ParticleSystemNode& container, sf::Time)
			{
			  if (container.getParticleType() == m_type)
				  m_particleSystem = &container;
			};
			Command command;
			command.NodeType = static_cast<unsigned int>(AlphaSquadron::NodeType::ParticleSystem);
			command.Action = Engine::DerivedAction<ParticleSystemNode>(finder);
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
		return {}; // Emitter has no visible bounds.
	}

	void EmitterNode::loadResources()
	{
		// No resources to load.
	}
}