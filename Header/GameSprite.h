//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef ALPHA_SQUADRON_HEADER_SPRITE_ENTITY_H_
#define ALPHA_SQUADRON_HEADER_SPRITE_ENTITY_H_

#include "Entity.h"
#include "DataCache.h"

 class GameSprite : public Entity
{
public:
	explicit GameSprite(const bool hasCollision, const TextureType textureType, const sf::IntRect textureRect = sf::IntRect())
					: m_textureType(textureType), m_textureRect(textureRect), Entity(hasCollision){}
	virtual ~GameSprite() override = default;
    void update(float deltaTime) override {}
	void render(sf::RenderWindow& renderWindow, sf::RenderStates states) override
	{
		if(!isActive())
			return;

		renderWindow.draw(m_sprite, states);
	}
	void collision(const Entity* other) override
	{
		if(!hasCollision())
			return;
	};
	bool isColliding(const sf::Rect<float>& bounds) const override
	{
		if(!hasCollision())
			return false;
		return m_sprite.getGlobalBounds().intersects(bounds);
	};
	sf::Rect<float> getGlobalBounds() override { return m_sprite.getGlobalBounds(); }
	sf::Vector2f getScaledTextureSize() const { return {(float)m_texture->getSize().x * m_sprite.getScale().x, (float)m_texture->getSize().y * m_sprite.getScale().y}; };
	void loadResources() override
	{
		m_texture = DataCache::getTexture(m_textureType, m_textureRect);
		m_sprite.setTexture(*m_texture);
	};
protected:
	 sf::Sprite m_sprite;
 private:
    sf::Texture* m_texture;
	TextureType m_textureType;
	sf::IntRect m_textureRect;
 };

#endif //ALPHA_SQUADRON_HEADER_SPRITE ENTITY_H_
