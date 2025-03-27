// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef GAMESPRITE_H_
#define GAMESPRITE_H_

#include "../Game/ResourceManager.h"
#include "Utility.h"

namespace Engine
{

	/**
	 * @file GameSprite.h
	 * @brief Declaration of the GameSprite class.
	 *
	 * The GameSprite class extends WorldNode to provide functionality for displaying a sprite,
	 * managing its movement via velocity, and handling resource loading.
	 */
	class GameSprite : public WorldNode
	{
	 public:
		/**
		 * @brief Constructs a GameSprite with collision enabled and an initial texture.
		 * @param hasCollision Whether collision is enabled for this sprite.
		 * @param textureId The texture identifier.
		 * @param centerOrigin If true, centers the origin of the sprite.
		 * @param textureLoadArea The area of the texture to load.
		 * @param spriteTextureRegion The region of the texture used for the sprite.
		 * @param repeatTexture If true, the texture will be repeated.
		 */
		explicit GameSprite(const bool hasCollision,
			const AlphaSquadron::TextureId textureId,
			const bool centerOrigin = false,
			const sf::IntRect textureLoadArea = sf::IntRect(),
			const sf::IntRect spriteTextureRegion = sf::IntRect(),
			bool repeatTexture = false)
			: m_textureId(textureId),
			  m_centerOrigin(centerOrigin),
			  m_textureLoadArea(textureLoadArea),
			  m_repeatTexture(repeatTexture),
			  m_spriteTextureRegion(spriteTextureRegion),
			  m_velocity(sf::Vector2f(0, 0)),
			  WorldNode(hasCollision)
		{
		}

		/**
		 * @brief Constructs a GameSprite with collision enabled without an initial texture.
		 * @param hasCollision Whether collision is enabled for this sprite.
		 * @param centerOrigin If true, centers the origin of the sprite.
		 * @param textureLoadArea The area of the texture to load.
		 * @param spriteTextureRegion The region of the texture used for the sprite.
		 * @param repeatTexture If true, the texture will be repeated.
		 */
		explicit GameSprite(const bool hasCollision,
			const bool centerOrigin = false,
			const sf::IntRect textureLoadArea = sf::IntRect(),
			const sf::IntRect spriteTextureRegion = sf::IntRect(),
			bool repeatTexture = false)
			: m_textureLoadArea(textureLoadArea),
			  m_textureId(),
			  m_centerOrigin(centerOrigin),
			  m_repeatTexture(repeatTexture),
			  m_spriteTextureRegion(spriteTextureRegion),
			  m_velocity(sf::Vector2f(0, 0)),
			  WorldNode(hasCollision)
		{
		}

		/// Default destructor.
		~GameSprite() override = default;

		/**
		 * @brief Retrieves the texture used by the sprite.
		 * @return Pointer to the texture.
		 */
		const sf::Texture* getTexture()
		{
			return m_sprite.getTexture();
		}

		/**
		 * @brief Sets the sprite's velocity.
		 * @param velocity The velocity vector.
		 */
		void setVelocity(sf::Vector2f velocity)
		{
			m_velocity = velocity;
		}

		/**
		 * @brief Sets the sprite's velocity.
		 * @param x The x-component of the velocity.
		 * @param y The y-component of the velocity.
		 */
		void setVelocity(float x, float y)
		{
			m_velocity.x = x;
			m_velocity.y = y;
		}

		/**
		 * @brief Gets the sprite's current velocity.
		 * @return The velocity vector.
		 */
		sf::Vector2f getVelocity() const
		{
			return m_velocity;
		}

		/**
		 * @brief Sets the text alpha.
		 * @param value value from 0-255 for alpha.
		 */
		void setAlpha(const int value)
		{
			m_sprite.setColor(sf::Color(m_sprite.getColor().r,m_sprite.getColor().g, m_sprite.getColor().b, value));
		}

		/**
		 * @brief Updates the sprite's position based on its velocity.
		 * @param deltaTime The time elapsed since the last update.
		 * @param commands The command queue.
		 */
		void update(sf::Time deltaTime, CommandQueue& commands) override
		{
			if (isActive())
			{ move(m_velocity * deltaTime.asSeconds()); }
		}

		/**
		 * @brief Retrieves the node type for the sprite.
		 * @return The combined node type flags.
		 */
		unsigned int getNodeType() const override
		{
			return WorldNode::getNodeType() | static_cast<unsigned int>(AlphaSquadron::NodeType::GameSprite);
		}

		/**
		 * @brief Gets the local bounds of the sprite.
		 * @return A rectangle representing the sprite's local bounds.
		 */
		sf::Rect<float> getLocalBounds() const
		{
			return m_sprite.getLocalBounds();
		}

		/**
		 * @brief Renders the sprite.
		 * @param renderTarget The target to draw on.
		 * @param states The render states.
		 */
		void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;

		/**
		 * @brief Draws the sprite's bounding rectangle (for debugging).
		 * @param target The render target.
		 * @param states The render states.
		 */
		void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

		/**
		 * @brief Loads the sprite's resources.
		 */
		void loadResources() override;

		/**
		 * @brief Gets the bounding rectangle of the sprite in world coordinates.
		 * @return The bounding rectangle.
		 */
		sf::FloatRect getBoundingRect() const override
		{
			auto gb = m_sprite.getGlobalBounds();
			auto rect = getWorldTransform().transformRect(gb);
			return rect;
		}

		/**
		 * @brief Sets the sprite's origin.
		 * @param x The x-coordinate.
		 * @param y The y-coordinate.
		 */
		void setSpriteOrigin(float x, float y)
		{
			m_sprite.setOrigin(x, y);
		}

		/**
		 * @brief Sets the color of the sprite.
		 * @param color The color to apply.
		 */
		void setColor(sf::Color color)
		{
			m_sprite.setColor(color);
		}

		/**
		 * @brief Sets the texture region for the sprite.
		 * @param rect The rectangle specifying the region.
		 */
		void setSpriteTextureRegion(sf::IntRect rect)
		{
			m_spriteTextureRegion = rect;
			m_sprite.setTextureRect(m_spriteTextureRegion);
		}

	 protected:
		/**
		 * @brief Sets the texture identifier.
		 * @param textureId The texture identifier.
		 */
		void setTextureId(AlphaSquadron::TextureId textureId)
		{
			m_textureId = textureId;
		}

		/**
		 * @brief Sets the texture load area.
		 * @param rect The rectangle specifying the texture area.
		 */
		void setTextureLoadArea(sf::IntRect rect)
		{
			m_textureLoadArea = rect;
		}

	 private:
		sf::Sprite m_sprite;               ///< The sprite object.
		AlphaSquadron::TextureId m_textureId;             ///< Identifier for the sprite's texture.
		sf::IntRect m_textureLoadArea;     ///< The area of the texture to load.
		sf::IntRect m_spriteTextureRegion; ///< The region of the texture used for the sprite.
		bool m_repeatTexture;              ///< Whether the texture should be repeated.
		bool m_centerOrigin;               ///< Whether to center the sprite's origin.
		sf::Vector2f m_velocity;           ///< The sprite's velocity.
	};
}
#endif // GAMESPRITE_H_
