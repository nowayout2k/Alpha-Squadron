//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef ALPHA_SQUADRON_PLAYER_H
#define ALPHA_SQUADRON_PLAYER_H


#include "Entity.h"
#include "Input.h"

class Player : public Entity
{
public:
    Player()
    {
        m_texture.loadFromFile("../Assets/Textures/Player.png");
        SetTexture(m_texture);
        SetScale(sf::Vector2f(.1,.1));

    }

private:
    sf::Texture m_texture;
};


#endif //ALPHA_SQUADRON_PLAYER_H
