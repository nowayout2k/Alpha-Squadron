//
// Created by Johnnie Otis on 6/1/24.
//

#ifndef ALPHA_SQUADRON_HEADER_ENEMY_H_
#define ALPHA_SQUADRON_HEADER_ENEMY_H_

#include "SpriteEntity.h"
#include "Entity.h"

class Enemy : public SpriteEntity
{
public:
    Enemy(bool hasCollision, sf::Vector2f position);
    void update(float deltaTime) override;
    void collision(const Entity* other) override;

private:
    sf::Texture m_texture;
	int m_health;
};


#endif //ALPHA_SQUADRON_HEADER_ENEMY_H_
