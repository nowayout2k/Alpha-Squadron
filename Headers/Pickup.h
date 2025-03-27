// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file Pickup.h
 * @brief Declaration of the Pickup class.
 *
 * This header declares the Pickup class, which represents collectible power-ups
 * that can modify an aircraft's attributes. The class derives from GameSprite and
 * integrates with the game's resource and update systems.
 */

#ifndef PICKUP_H_
#define PICKUP_H_

#include "Aircraft.h"
#include "PickupType.h"

/**
 * @class Pickup
 * @brief Represents a pickup item in the game.
 *
 * The Pickup class is responsible for managing power-up items that provide
 * benefits to an aircraft, such as health refills or weapon upgrades.
 * It handles resource loading, rendering, and applying the pickup effect.
 */
class Pickup : public GameSprite
{
 public:
	/**
	 * @brief Constructs a Pickup.
	 * @param type The type of pickup (e.g., HealthRefill, MissileRefill).
	 */
	explicit Pickup(PickupType type);

	/**
	 * @brief Retrieves the composite node type.
	 * @return The node type flags combined with the Pickup flag.
	 */
	unsigned int getNodeType() const override { return GameSprite::getNodeType() | (unsigned int)NodeType::Pickup; }

	/**
	 * @brief Sets the color of the pickup based on its type.
	 *
	 * This function changes the pickup's color to visually indicate its effect.
	 */
	void setPickupColor();

	/**
	 * @brief Applies the pickup's effect to the specified aircraft.
	 * @param player The aircraft to which the pickup effect is applied.
	 */
	void apply(Aircraft& player) const;

	/**
	 * @brief Updates the pickup's state.
	 * @param deltaTime The time elapsed since the last update.
	 * @param commands The command queue used for game commands.
	 */
	void update(sf::Time deltaTime, CommandQueue& commands) override;

	/**
	 * @brief Loads the necessary resources for the pickup.
	 *
	 * Loads textures and actions associated with the pickup type from the game data.
	 */
	void loadResources() override;

 protected:
	/**
	 * @brief Renders the pickup.
	 * @param renderTarget The target to draw on.
	 * @param states The current render states.
	 */
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;

 private:
	PickupType m_pickupType;               ///< The type of the pickup.
	sf::Sprite m_sprite;                   ///< The sprite used to display the pickup.
	std::function<void(Aircraft&)> m_action; ///< The action to apply to an aircraft when the pickup is collected.
};

#endif //PICKUP_H_
