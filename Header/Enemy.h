//
// Created by Johnnie Otis on 6/1/24.
//

#ifndef ENEMY_H_
#define ENEMY_H_

#include "GameSprite.h"
#include "Entity.h"
#include "Character.h"

class Enemy : public Character
{
public:
	explicit Enemy(bool hasCollision, sf::Vector2f position);
    void update(float deltaTime) override;
    void collision(const Entity* other) override;
private:
    sf::Texture m_texture;
};

#endif //ENEMY_H_
