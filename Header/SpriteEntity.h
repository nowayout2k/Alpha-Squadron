//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef ALPHA_SQUADRON_HEADER_SPRITE_ENTITY_H_
#define ALPHA_SQUADRON_HEADER_SPRITE_ENTITY_H_

#include "Entity.h"
#include "DataCache.h"

 class SpriteEntity : public sf::Sprite, public Entity
{
public:
	explicit SpriteEntity(const bool hasCollision, const std::string& pathToTexture, const sf::IntRect textureRect = sf::IntRect()) : m_hasCollision(hasCollision)
	{
		m_texture = loadTexture(pathToTexture, textureRect);
		setTexture(*m_texture);
	}
	virtual ~SpriteEntity() override = default;
    void update(float deltaTime) override { Entity::update(deltaTime); };
    virtual void collision(const Entity* other) { if(!m_hasCollision) return; };
    bool isColliding(const sf::Rect<float>& bounds) const { return m_hasCollision && getGlobalBounds().intersects(bounds); }
	bool hasCollision() const { return m_hasCollision; }
	void setCollision(bool hasCollision) { m_hasCollision = hasCollision; };
	sf::Vector2f getScaledTextureSize() const { return {(float)m_texture->getSize().x * getScale().x, (float)m_texture->getSize().y * getScale().y}; };

protected:
    std::shared_ptr<sf::Texture> loadTexture(const std::string &pathToTexture, const sf::IntRect textureRect = sf::IntRect())
	{
		return DataCache::getTexture(pathToTexture, textureRect);
	}
 private:
    std::shared_ptr<sf::Texture> m_texture;
	bool m_hasCollision;
};

#endif //ALPHA_SQUADRON_HEADER_SPRITE ENTITY_H_
