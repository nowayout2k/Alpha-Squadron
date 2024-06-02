//
// Created by Johnnie Otis on 6/1/24.
//

#ifndef ALPHA_SQUADRON_ENEMY_H
#define ALPHA_SQUADRON_ENEMY_H


#include "Entity.h"

class Enemy : public Entity
{
public:
    Enemy();
    void Update() override;
    void Collision(const Entity* other) override;

private:
    sf::Texture m_texture;
};


#endif //ALPHA_SQUADRON_ENEMY_H
