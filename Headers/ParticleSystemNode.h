// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file ParticleSystemNode.h
 * @brief Declaration of the ParticleSystemNode class.
 *
 * This header declares the ParticleSystemNode class, which manages a collection
 * of particles for visual effects. It handles particle addition, updating their
 * states, and rendering them using a vertex array.
 */

#ifndef ALPHA_SQUADRON_HEADERS_PARTICLESYSTEMNODE_H_
#define ALPHA_SQUADRON_HEADERS_PARTICLESYSTEMNODE_H_

#include "World.h"      ///< Provides WorldNode and game world context.
#include "Particle.h"   ///< Defines the Particle structure and types.

/**
 * @class ParticleSystemNode
 * @brief A world node that renders and updates a particle system.
 *
 * The ParticleSystemNode class manages a collection of particles, updating their
 * lifetimes and positions, and renders them efficiently using a vertex array.
 * It supports different particle types defined in the Particle structure.
 */
class ParticleSystemNode : public WorldNode
{
 public:
	/**
	 * @brief Constructs a ParticleSystemNode.
	 * @param type The type of particles managed by this system.
	 */
	explicit ParticleSystemNode(Particle::Type type);

	/**
	 * @brief Adds a new particle to the system.
	 * @param position The spawn position of the new particle.
	 */
	void addParticle(sf::Vector2f position);

	/**
	 * @brief Retrieves the particle type of this system.
	 * @return The Particle::Type of the particles.
	 */
	Particle::Type getParticleType() const { return m_type; };

	/**
	 * @brief Retrieves the composite node type.
	 * @return The combined node type flags for WorldNode and ParticleSystem.
	 */
	unsigned int getNodeType() const override { return WorldNode::getNodeType() | static_cast<unsigned int>(NodeType::ParticleSystem); }

	/**
	 * @brief Updates particle lifetimes and marks vertex data for update.
	 * @param deltaTime The elapsed time since the last update.
	 * @param commands The command queue for issuing game commands.
	 */
	void update(sf::Time deltaTime, CommandQueue& commands) override;

	/**
	 * @brief Renders the particle system.
	 * @param target The render target.
	 * @param states The current render states.
	 */
	void render(sf::RenderTarget& target, sf::RenderStates states) const override;

	/**
	 * @brief Returns the bounding rectangle of the particle system.
	 * @return An empty rectangle as particles are dynamically positioned.
	 */
	sf::Rect<float> getBoundingRect() const override;

 protected:
	/**
	 * @brief Loads any necessary resources.
	 *
	 * Currently, this function is empty because resource loading is handled externally.
	 */
	void loadResources() override;

 private:
	/**
	 * @brief Computes the vertices for all active particles.
	 *
	 * Updates the mutable vertex array based on the current state of all particles.
	 */
	void computeVertices() const;

	/**
	 * @brief Appends a vertex to the vertex array.
	 * @param worldX The x-coordinate in world space.
	 * @param worldY The y-coordinate in world space.
	 * @param texCoordX The x-coordinate for texture mapping.
	 * @param texCoordY The y-coordinate for texture mapping.
	 * @param color The color of the vertex.
	 */
	void addVertex(float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const;

	// Member variables:

	std::deque<Particle> m_particles;  ///< Deque storing active particles.
	const sf::Texture& m_texture;        ///< Reference to the texture used for particles.
	Particle::Type m_type;               ///< The type of particles managed.
	mutable sf::VertexArray m_vertexArray; ///< Mutable vertex array for rendering particles.
	mutable bool m_needsVertexUpdate;    ///< Flag to indicate if vertex array needs recomputation.
};

#endif //ALPHA_SQUADRON_HEADERS_PARTICLESYSTEMNODE_H_
