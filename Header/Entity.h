//
// Created by Johnnie on 5/29/2024.
//

#ifndef ALPHA_SQUADRON_HEADER_ENTITY_H_
#define ALPHA_SQUADRON_HEADER_ENTITY_H_

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector3.hpp>

class Entity : public sf::Drawable, public sf::Transformable
{
 public:
    virtual void Update(float deltaTime) = 0;
    virtual void Collision(const Entity* other) = 0;
protected:
    Entity() = default;
    sf::Drawable* m_drawable;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(*m_drawable, states.transform *= getTransform());
    };
};

#endif //ALPHA_SQUADRON_HEADER_ENTITY_H_
