//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef ALPHA_SQUADRON_SPRITEENTITY_H
#define ALPHA_SQUADRON_SPRITEENTITY_H


#include "Entity.h"
#include "WindowManager.h"
#include "Logger.h"

class SpriteEntity : public Entity
{
public:
    virtual void Update(float deltaTime) = 0;
    virtual void Collision(const Entity* other) { if(!hasCollision) return; };
    bool IsColliding(const sf::Rect<float>& bounds) const { return hasCollision && GetGlobalBounds().intersects(bounds); }
    sf::Rect<float> GetGlobalBounds() const { return getTransform().transformRect(m_sprite->getGlobalBounds()); };
protected:
    explicit SpriteEntity(const std::string &pathToTexture, const bool hasCollision) : hasCollision(hasCollision)
    {
        if (!m_texture.loadFromFile(pathToTexture))
        {
            Logger::Log(LogType::Error, "Texture not found at: " + pathToTexture);
            return;
        }
        m_sprite = std::make_unique<sf::Sprite>(m_texture);
        m_drawable = m_sprite.get();
    }
    std::shared_ptr<sf::Sprite> m_sprite;
    sf::Texture m_texture;
private:
    bool hasCollision;
};

#endif //ALPHA_SQUADRON_SPRITEENTITY_H