// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON__UI_H_
#define ALPHA_SQUADRON__UI_H_

#include "WorldNode.h"
#include "GameSprite.h"
#include "GameText.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>

/**
 * @file CanvasNode.h
 * @brief Declaration of the CanvasNode class.
 *
 * The CanvasNode class is a UI element that displays health information for players.
 * It manages health bar, background, and text elements, and updates its layout based on the view.
 */
class CanvasNode : public WorldNode
{
 public:
	/**
	 * @brief Constructs a CanvasNode.
	 *
	 * Creates the UI elements for displaying player health.
	 */
	explicit CanvasNode();

	/**
	 * @brief Retrieves the bounding rectangle for the CanvasNode.
	 *
	 * The bounding rectangle is determined by the size of the world view.
	 *
	 * @return A FloatRect representing the bounding rectangle.
	 */
	sf::FloatRect getBoundingRect() const override;

	/**
	 * @brief Retrieves the node type.
	 *
	 * The node type is combined with the UI canvas flag.
	 *
	 * @return An unsigned integer representing the node type.
	 */
	unsigned int getNodeType() const override;

	/**
	 * @brief Retrieves the local bounds of the CanvasNode.
	 *
	 * @return A FloatRect representing the local bounds.
	 */
	sf::FloatRect getLocalBounds() const;

	/**
	 * @brief Updates the CanvasNode.
	 *
	 * Updates the positions and scales of the UI elements based on the view.
	 *
	 * @param deltaTime Time elapsed since the last update.
	 * @param commands Command queue for issuing commands.
	 */
	void update(sf::Time deltaTime, CommandQueue& commands) override;

	/**
	 * @brief Sets the health value for a given player.
	 *
	 * Updates the health for the specified player, clamping to a minimum of 0.
	 *
	 * @param health The new health value.
	 * @param playerNum The index of the player.
	 */
	void setHeath(float health, int playerNum);

 protected:
	/**
	 * @brief Renders the CanvasNode's UI elements.
	 *
	 * Draws the health background and health bar elements.
	 *
	 * @param target The render target.
	 * @param states The current render states.
	 */
	void render(sf::RenderTarget& target, sf::RenderStates states) const override;

	/**
	 * @brief Loads the UI resources.
	 *
	 * Loads the resources for the health UI elements and adjusts their layout.
	 */
	void loadResources() override;

 private:
	std::vector<float> m_playerHealths;   // Health values for players.
	GameSprite* m_healthBgElement;          // Pointer to the health background sprite.
	GameSprite* m_healthBarElement;         // Pointer to the health bar sprite.
	GameText* m_healthTextElement;          // Pointer to the health text element.
};

#endif // ALPHA_SQUADRON__UI_H_
