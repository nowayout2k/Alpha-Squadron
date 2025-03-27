// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON__UI_H_
#define ALPHA_SQUADRON__UI_H_

#include "../Engine/WorldNode.h"
#include "../Engine/GameSprite.h"
#include "../Engine/GameText.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>
namespace AlphaSquadron
{
	/**
	 * @file CanvasNode.h
	 * @brief Declaration of the CanvasNode class.
	 *
	 * The CanvasNode class is a UI element that displays health information for players.
	 * It manages health bar, background, and text elements, and updates its layout based on the view.
	 */
 class CanvasNode : public Engine::WorldNode
	{
	 public:
		/**
		 * @brief Constructs a CanvasNode.
		 *
		 * Creates the UI elements for displaying player health.
		 */
		explicit CanvasNode();

	 	/**
		* @brief Adds the ui for player 2.
		*
		* Creates the UI elements for displaying player health for player 2.
		*/
	 	void addPlayer2Ui();

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
		void update(sf::Time deltaTime, Engine::CommandQueue& commands) override;

		/**
		 * @brief Sets the health value for a given player.
		 *
		 * Updates the health for the specified player, clamping to a minimum of 0.
		 *
		 * @param health The new health value.
		 * @param playerNum The index of the player.
		 */
		void setHeath(float health, bool isPlayer1);

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
		float m_player1Health; 							///< Health value for player 1.
	 	float m_player2Health; 							///< Health value for player 2.
		Engine::GameSprite* m_healthBgElement1;        ///< Pointer to the health background sprite for player 1.
		Engine::GameSprite* m_healthBarElement1;     ///< Pointer to the health bar sprite for player 1.
		Engine::GameText* m_healthTextElement1;      ///< Pointer to the health text element for player 1.
		Engine::GameSprite* m_healthBgElement2;        ///< Pointer to the health background sprite for player 2.
	 	Engine::GameSprite* m_healthBarElement2;     ///< Pointer to the health bar sprite for player 2.
	 	Engine::GameText* m_healthTextElement2;      ///< Pointer to the health text element for player 2.
	};
}
#endif // ALPHA_SQUADRON__UI_H_
