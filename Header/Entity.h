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
    virtual void update(float deltaTime) { if(!m_isAlive) return; };
    virtual void collision(const Entity* other) = 0;
	bool isAlive() const { return m_isAlive;};
protected:
    Entity(){ m_isAlive = true; };
    sf::Drawable* m_drawable;
	bool m_isAlive;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(*m_drawable, states.transform *= getTransform());
    };
};

#endif //ALPHA_SQUADRON_HEADER_ENTITY_H_
