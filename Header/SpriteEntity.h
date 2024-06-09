//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef ALPHA_SQUADRON_HEADER_SPRITE_ENTITY_H_
#define ALPHA_SQUADRON_HEADER_SPRITE_ENTITY_H_


#include "WindowManager.h"
#include "Logger.h"
#include "Entity.h"
#include "DrawableEntity.h"

class SpriteEntity : public DrawableEntity
{
public:
    virtual void update(float deltaTime) = 0;
    virtual void collision(const Entity* other) { if(!m_hasCollision) return; };
    bool isColliding(const sf::Rect<float>& bounds) const { return m_hasCollision && getGlobalBounds().intersects(bounds); }
    sf::Rect<float> getGlobalBounds() const { return getTransform().transformRect(m_sprite->getGlobalBounds()); };
	bool hasCollision() const { return m_hasCollision; }
protected:
    explicit SpriteEntity(const bool hasCollision, const std::string& pathToTexture, const sf::IntRect textureRect = sf::IntRect()) : m_hasCollision(hasCollision)
    {
		loadTexture(pathToTexture, textureRect);
        m_sprite = std::make_unique<sf::Sprite>(m_texture);
		addDrawable(m_sprite.get(), true);
    }

    bool loadTexture(const std::string &pathToTexture, const sf::IntRect textureRect = sf::IntRect())
    {
		if(textureRect == sf::IntRect())
		{
			if (!m_texture.loadFromFile(pathToTexture))
			{
				Logger::Log(LogType::Error, "Texture not found at: " + pathToTexture);
				return false;
			}
		}
		else
		{
			if (!m_texture.loadFromFile(pathToTexture, textureRect))
			{
				Logger::Log(LogType::Error, "Texture not found at: " + pathToTexture);
				return false;
			}
		}
		return true;
    }

    std::unique_ptr<sf::Sprite> m_sprite;
    sf::Texture m_texture;
	bool m_hasCollision;
};

#endif //ALPHA_SQUADRON_HEADER_SPRITE ENTITY_H_
