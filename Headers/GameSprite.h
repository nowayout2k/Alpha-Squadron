// Copyright (c) 2025 No Way Out LLC All rights reserved.

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

	const sf::Texture* getTexture()
	{
		return m_sprite.getTexture();
	}

	unsigned int getNodeType() const override { return Entity::getNodeType() | (unsigned int)NodeType::Sprite; }

	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override
	{
		renderTarget.draw(m_sprite, states);
		if(Debug::isCollidersVisible())
			drawBoundingRect(renderTarget, states);
	}

	sf::Rect<float> getLocalBounds() const
	{
		return m_sprite.getLocalBounds();
	}

	void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
	{
		sf::FloatRect rect = getBoundingRect();

		//Bounding box
		sf::RectangleShape rectangleShape;
		rectangleShape.setPosition(sf::Vector2f(rect.left, rect.top));
		rectangleShape.setSize(sf::Vector2f(rect.width, rect.height));
		rectangleShape.setFillColor(sf::Color::Transparent);
		rectangleShape.setOutlineColor(sf::Color::Green);
		rectangleShape.setOutlineThickness(3.f);

		//Pivot Point
		sf::CircleShape circleShape;
		circleShape.setPosition(getPosition().x + (getOrigin().x * rect.width), getPosition().y + (getOrigin().y * rect.height));
		circleShape.setRadius(1.f);
		circleShape.setFillColor(sf::Color::Red);
		circleShape.setOutlineColor(sf::Color::Red);
		circleShape.setOutlineThickness(3.f);

		target.draw(rectangleShape);
		target.draw(circleShape);
	}

	sf::FloatRect getBoundingRect() const override
	{
		return getWorldTransform().transformRect(m_sprite.getGlobalBounds());
	}

	void setSpriteOrigin(float x, float y)
	{
		m_sprite.setOrigin(x,y);
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
	void setSpriteTextureRegion(sf::IntRect rect) { m_spriteTextureRegion = rect; m_sprite.setTextureRect(m_spriteTextureRegion); }
 protected:
	void setTextureId(TextureId textureId) { m_textureId = textureId; }
	void setTextureLoadArea(sf::IntRect rect) { m_textureLoadArea = rect; }

 private:
	sf::Sprite m_sprite;
	TextureId m_textureId;
	sf::IntRect m_textureLoadArea;
	sf::IntRect m_spriteTextureRegion;
	bool m_repeatTexture;
	bool m_centerOrigin;
 };

#endif //GAMESPRITE_H_
