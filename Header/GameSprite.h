//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef GAMESPRITE_H_
#define GAMESPRITE_H_

#include "Entity.h"
#include "ResourceManager.h"

class GameSprite : public Entity
{
public:
	explicit GameSprite(EntityType entityType, const bool hasCollision, const TextureId textureType,
		const sf::IntRect textureRect = sf::IntRect(), bool repeatTexture = false) : m_textureId(textureType),
		m_textureRect(textureRect), m_repeatTexture(repeatTexture), Entity(entityType, hasCollision){}
	virtual ~GameSprite() override = default;

	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override
	{
		renderTarget.draw(m_sprite, states);
	}

	void collision(const Entity* other) override
	{
		if(!hasCollision())
			return;
	}

	bool isColliding(const sf::Rect<float>& bounds) const override
	{
		if(!hasCollision())
			return false;

		return getGlobalBounds().intersects(bounds);
	}

	sf::Rect<float> getGlobalBounds() const override
	{
		sf::FloatRect bounds = m_sprite.getGlobalBounds();
		return getTransform().transformRect(bounds);
	}

	void loadResources() override
	{
		auto& tex = ResourceManager::loadResource(m_textureId, m_textureRect);
		tex.setRepeated(m_repeatTexture);
		m_sprite.setTexture(tex);
	}

	void setColor(sf::Color color)
	{
		m_sprite.setColor(color);
	}

 private:
	sf::Sprite m_sprite;
	TextureId m_textureId;
	sf::IntRect m_textureRect;
	bool m_repeatTexture;
 };

#endif //ALPHA_SQUADRON_HEADER_SPRITE ENTITY_H_
