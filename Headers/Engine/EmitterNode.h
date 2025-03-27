// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON_HEADERS_EMITTERNODE_H_
#define ALPHA_SQUADRON_HEADERS_EMITTERNODE_H_

#include "Particle.h"
#include "WorldNode.h"
#include "ParticleSystemNode.h"
#include "../Game/ParticleType.h"
namespace Engine
{
	/**
	 * @file EmitterNode.h
	 * @brief Declaration of the EmitterNode class.
	 *
	 * The EmitterNode class is a specialized WorldNode that emits particles of a specified type.
	 * It locates a matching ParticleSystemNode and, once found, continuously emits particles at a fixed rate.
	 */
	class EmitterNode : public WorldNode
	{
	 public:
		/**
		 * @brief Constructs an EmitterNode for a given particle type.
		 * @param type The particle type to emit.
		 */
		explicit EmitterNode(AlphaSquadron::ParticleType type);

		/**
		 * @brief Retrieves the bounding rectangle of the emitter.
		 * @return An empty rectangle as the emitter has no visual bounds.
		 */
		sf::Rect<float> getBoundingRect() const override;

	 protected:
		/**
		 * @brief Renders the emitter.
		 *
		 * This function is intentionally left empty as the emitter itself does not render anything.
		 *
		 * @param renderTarget The render target.
		 * @param states The current render states.
		 */
		void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;

		/**
		 * @brief Updates the emitter.
		 *
		 * If a matching ParticleSystemNode is found, emits particles based on the elapsed time.
		 * Otherwise, sends a command to locate the appropriate ParticleSystemNode.
		 *
		 * @param deltaTime The time elapsed since the last update.
		 * @param commands The command queue for issuing commands.
		 */
		void update(sf::Time deltaTime, CommandQueue& commands) override;

		/**
		 * @brief Loads any necessary resources.
		 *
		 * Currently, this function does not perform any operations.
		 */
		void loadResources() override;

	 private:
		/**
		 * @brief Emits particles based on the elapsed time.
		 *
		 * Particles are emitted at a fixed rate by accumulating delta time until a threshold is reached.
		 *
		 * @param dt The time elapsed since the last update.
		 */
		void emitParticles(sf::Time dt);

		sf::Time m_accumulatedTime;           ///< Accumulated time used to determine when to emit a new particle.
		AlphaSquadron::ParticleType m_type;                ///< The type of particles to emit.
		ParticleSystemNode* m_particleSystem{}; ///< Pointer to the matching ParticleSystemNode, if found.
	};
}
#endif // ALPHA_SQUADRON_HEADERS_EMITTERNODE_H_
