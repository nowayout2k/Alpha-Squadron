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

class Entity : public sf::Drawable
{
 public:
    sf::Vector2f GetPosition() { m_sprite.getPosition(); };
    float GetRotation() { m_sprite.getRotation(); };
    sf::Vector2f GetScale() { m_sprite.getScale(); };

    void SetPosition(sf::Vector2f position) { m_sprite.setPosition(position); };
    void SetRotation(float angle) { m_sprite.setRotation(angle); };
    void SetScale(sf::Vector2f factors) { m_sprite.setScale(factors); };

    void MovePosition(sf::Vector2f offset) { m_sprite.move(offset); };
protected:
    void SetTexture(sf::Texture& texture) { m_sprite.setTexture(texture); }
    Entity() {};

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(m_sprite, states); };
	sf::Sprite m_sprite;
};

#endif //ALPHA_SQUADRON_HEADER_ENTITY_H_
