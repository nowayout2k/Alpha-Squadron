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
		const sf::IntRect textureRect = sf::IntRect()) : m_textureId(textureType),
		m_textureRect(textureRect), Entity(entityType, hasCollision){}
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
		return m_sprite.getGlobalBounds().intersects(bounds);
	}
	sf::Rect<float> getGlobalBounds() override { return m_sprite.getGlobalBounds(); }
	sf::Vector2f getScaledTextureSize() const
	{
		return {
			(float)m_sprite.getTexture()->getSize().x * m_sprite.getScale().x,
			(float)m_sprite.getTexture()->getSize().y * m_sprite.getScale().y
		};
	}
	void loadResources() override
	{
		m_sprite.setTexture(ResourceManager::loadResource(m_textureId, m_textureRect));
	}
protected:
	 sf::Sprite m_sprite;
 private:
	TextureId m_textureId;
	sf::IntRect m_textureRect;
 };

#endif //ALPHA_SQUADRON_HEADER_SPRITE ENTITY_H_
