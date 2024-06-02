//
// Created by Johnnie Otis on 6/2/24.
//

#ifndef ALPHA_SQUADRON_HEADER_PLAYER_H_
#define ALPHA_SQUADRON_HEADER_PLAYER_H_


#include "SpriteEntity.h"

class Player : public SpriteEntity
{
public:
    explicit Player(const bool hasCollision);
    void update(float deltaTime) override;
    void collision(const Entity* other) override;
private:
    sf::Vector2f handleInput();
    void adjustOffsetToWindow(sf::Vector2f& offset);
};


#endif //ALPHA_SQUADRON_HEADER_PLAYER_H_
