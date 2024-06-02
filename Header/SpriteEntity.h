//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef ALPHA_SQUADRON_HEADER_SPRITE_ENTITY_H_
#define ALPHA_SQUADRON_HEADER_SPRITE_ENTITY_H_


#include "Entity.h"
#include "WindowManager.h"
#include "Logger.h"

class SpriteEntity : public Entity
{
public:
    virtual void update(float deltaTime) = 0;
    virtual void collision(const Entity* other) { if(!m_hasCollision) return; };
    bool isColliding(const sf::Rect<float>& bounds) const { return m_hasCollision && getGlobalBounds().intersects(bounds); }
    sf::Rect<float> getGlobalBounds() const { return getTransform().transformRect(m_sprite->getGlobalBounds()); };
protected:
    explicit SpriteEntity(const bool hasCollision, const std::string &pathToTexture, const sf::IntRect textureRect = sf::IntRect()) : m_hasCollision(hasCollision)
    {
        if(textureRect == sf::IntRect())
        {
            if (!m_texture.loadFromFile(pathToTexture))
            {
                Logger::Log(LogType::Error, "Texture not found at: " + pathToTexture);
                return;
            }
        }
        else
        {
            if (!m_texture.loadFromFile(pathToTexture, textureRect))
            {
                Logger::Log(LogType::Error, "Texture not found at: " + pathToTexture);
                return;
            }
        }
        m_sprite = std::make_unique<sf::Sprite>(m_texture);
        m_drawable = m_sprite.get();
    }

    void loadTexture(const std::string &pathToTexture, const sf::IntRect textureRect)
    {
        if (!m_texture.loadFromFile(pathToTexture, textureRect))
        {
            Logger::Log(LogType::Error, "Texture not found at: " + pathToTexture);
            return;
        }
    }

    std::shared_ptr<sf::Sprite> m_sprite;
    sf::Texture m_texture;
private:
    bool m_hasCollision;
};

#endif //ALPHA_SQUADRON_HEADER_SPRITE ENTITY_H_
