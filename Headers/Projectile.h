// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file Projectile.h
 * @brief Declaration of the Projectile class.
 *
 * This header declares the Projectile class, which represents projectiles in the game.
 * It defines interfaces for updating, rendering, guiding, and loading resources for projectiles.
 * The class supports both guided (missiles) and non-guided (bullets) projectiles.
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameSprite.h"
#include "CommandQueue.h"
#include "ProjectileType.h"

namespace AlphaSquadron
{
	/**
	 * @class Projectile
	 * @brief Represents a projectile in the game.
	 *
	 * The Projectile class extends GameSprite to encapsulate projectile-specific behavior.
	 * It supports guided movement (for missiles) and linear motion (for bullets). Additionally,
	 * it provides interfaces to update its state, render itself, adjust its guidance direction,
	 * and load the appropriate resources.
	 */
	class Projectile : public Engine::GameSprite
	{
	 public:
		/**
		 * @brief Constructs a Projectile.
		 * @param type The node type for the projectile (e.g., allied or enemy).
		 * @param projectileType The type of projectile (Bullet or Missile).
		 * @param targetDirection The desired direction for guided projectiles.
		 * @param launchDirection The initial launch direction.
		 */
		explicit Projectile(NodeType type,
			ProjectileType projectileType,
			sf::Vector2f targetDirection,
			sf::Vector2f launchDirection);

		/**
		 * @brief Updates the projectile's state.
		 * @param deltaTime The time elapsed since the last update.
		 * @param commands The command queue to which any generated commands are pushed.
		 *
		 * Handles launch timing, guided trajectory adjustments for missiles, and linear motion for bullets.
		 */
		void update(sf::Time deltaTime, Engine::CommandQueue& commands) override;

		/**
		 * @brief Renders the projectile.
		 * @param renderTarget The render target to draw the projectile on.
		 * @param states The current render states.
		 */
		void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;

		/**
		 * @brief Adjusts the projectile's guidance direction.
		 * @param position The target position to guide the projectile towards.
		 */
		void guideTowards(sf::Vector2f position);

		/**
		 * @brief Checks if the projectile is guided.
		 * @return True if the projectile is guided (i.e., a missile); false otherwise.
		 */
		bool isGuided() const;

		/**
		 * @brief Retrieves the composite node type.
		 * @return The node type flags combined with the projectile's specific type.
		 */
		unsigned int getNodeType() const override
		{
			return GameSprite::getNodeType() | static_cast<unsigned int>(m_type);
		}

		/**
		 * @brief Gets the maximum speed of the projectile.
		 * @return The maximum speed value.
		 */
		float getMaxSpeed() const;

		/**
		 * @brief Retrieves the damage dealt by the projectile.
		 * @return The damage value.
		 */
		float getDamage();

		/**
		 * @brief Loads the necessary resources for the projectile.
		 *
		 * Loads textures and other resource data based on the projectile type from the game data.
		 */
		void loadResources() override;

	 private:
		sf::Vector2f m_targetDirection; ///< Desired direction for guided projectiles.
		sf::Vector2f m_launchDirection;   ///< Initial launch direction for the projectile.
		ProjectileType m_projectileType;  ///< The type of projectile (Bullet or Missile).
		NodeType m_type;                  ///< The node type for the projectile.
		bool m_isLaunching;               ///< Flag indicating if the projectile is still in its launch phase.
		float m_timeSinceLaunch;          ///< Time elapsed since the projectile was launched.
		float m_maxSpeed;                 ///< Maximum speed of the projectile.
	};
}
#endif //PROJECTILE_H_
