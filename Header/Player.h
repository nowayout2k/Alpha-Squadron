//
// Created by Johnnie Otis on 6/2/24.
//

#ifndef PLAYER_H_
#define PLAYER_H_


#include "GameSprite.h"
#include "Entity.h"
#include "Character.h"


class Player : public Character
{
public:
    explicit Player();
    void update(float deltaTime) override;
    void collision(const Entity* other) override;
private:
    sf::Vector2f handleInput(float deltaTime);
    void adjustOffsetToWindow(sf::Vector2f& offset);
};

#endif //PLAYER_H_
