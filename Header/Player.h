//
// Created by Johnnie Otis on 6/2/24.
//

#ifndef ALPHA_SQUADRON_PLAYER_H
#define ALPHA_SQUADRON_PLAYER_H


#include "SpriteEntity.h"

class Player : public SpriteEntity
{
public:
    explicit Player(const bool hasCollision);
    void Update(float deltaTime) override;
    void Collision(const Entity* other) override;
private:
    sf::Vector2f HandleInput();
    void AdjustOffsetToWindow(sf::Vector2f& offset);
};


#endif //ALPHA_SQUADRON_PLAYER_H
