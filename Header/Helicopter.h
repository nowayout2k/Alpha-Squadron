//
// Created by Johnnie Otis on 6/1/24.
//

#ifndef HELICOPTER_H_
#define HELICOPTER_H_

#include "GameSprite.h"
#include "Entity.h"
#include "Character.h"

class Helicopter : public Character
{
public:
	explicit Helicopter(bool hasCollision, sf::Vector2f position);
    void update(float deltaTime) override;
    void collision(const Entity* other) override;
private:
    sf::Texture m_texture;
};

#endif //HELICOPTER_H_
