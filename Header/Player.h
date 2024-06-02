//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef ALPHA_SQUADRON_PLAYER_H
#define ALPHA_SQUADRON_PLAYER_H


#include "Entity.h"

class Player : public Entity
{
public:
    Player();
    void Update() override;
    void Collision(const Entity* other) override;

private:
    sf::Texture m_texture;
};


#endif //ALPHA_SQUADRON_PLAYER_H
