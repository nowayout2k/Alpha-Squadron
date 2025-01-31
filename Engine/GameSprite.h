//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef GAMESPRITE_H_
#define GAMESPRITE_H_

#include "Entity.h"
#include "ResourceManager.h"
#include "Utility.h"

class GameSprite : public Entity
{
public:
	explicit GameSprite(const bool hasCollision, const TextureId textureId, const bool centerOrigin = false,
		const sf::IntRect textureLoadArea = sf::IntRect(), const sf::IntRect spriteTextureRegion = sf::IntRect(), bool repeatTexture = false)
		: m_textureId(textureId), m_centerOrigin(centerOrigin), m_textureLoadArea(textureLoadArea), m_repeatTexture(repeatTexture), m_spriteTextureRegion(spriteTextureRegion),
		  Entity(hasCollision)
		{
		}

	explicit GameSprite(const bool hasCollision, const bool centerOrigin = false,
		const sf::IntRect textureLoadArea = sf::IntRect(), const sf::IntRect spriteTextureRegion = sf::IntRect(), bool repeatTexture = false)
		: m_textureLoadArea(textureLoadArea), m_textureId(), m_centerOrigin(centerOrigin), m_repeatTexture(repeatTexture), m_spriteTextureRegion(spriteTextureRegion),
		  Entity(hasCollision)
	{
	}

	~GameSprite() override = default;

	unsigned int getNodeType() const override { return Entity::getNodeType() | (unsigned int)NodeType::Sprite; }

	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override
	{
		renderTarget.draw(m_sprite, states);
		if(Debug::isCollidersVisible())
			drawBoundingRect(renderTarget, states);
	}

	sf::Rect<float> getGlobalBounds() const override
	{
		return m_sprite.getGlobalBounds();
	}

	sf::Rect<float> getLocalBounds() const
	{
		return m_sprite.getLocalBounds();
	}

	void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
	{
		sf::FloatRect rect = getBoundingRect();

		sf::RectangleShape shape;
		shape.setPosition(sf::Vector2f(rect.left, rect.top));
		shape.setSize(sf::Vector2f(rect.width, rect.height));
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Green);
		shape.setOutlineThickness(3.f);

		target.draw(shape);
	}

	sf::FloatRect getBoundingRect() const override
	{
		return getWorldTransform().transformRect(m_sprite.getGlobalBounds());
	}

	void loadResources() override
	{
		auto& tex = ResourceManager::loadResource(m_textureId, m_textureLoadArea);
		tex.setRepeated(m_repeatTexture);
		m_sprite.setTexture(tex);
		if(m_spriteTextureRegion != sf::IntRect())
			m_sprite.setTextureRect(m_spriteTextureRegion);
		if(m_centerOrigin)
			Utility::centerOrigin(m_sprite);
	}

	void setColor(sf::Color color)
	{
		m_sprite.setColor(color);
	}

 protected:
	void setTextureId(TextureId textureId) { m_textureId = textureId; }
	void setTextureLoadArea(sf::IntRect rect) { m_textureLoadArea = rect; }
	void setSpriteTextureRegion(sf::IntRect rect) { m_spriteTextureRegion = rect; }
 private:
	sf::Sprite m_sprite;
	TextureId m_textureId;
	sf::IntRect m_textureLoadArea;
	sf::IntRect m_spriteTextureRegion;
	bool m_repeatTexture;
	bool m_centerOrigin;
 };

#endif //GAMESPRITE_H_
