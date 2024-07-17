//
// Created by Johnnie Otis on 6/2/24.
//

#ifndef PLAYERAIRCRAFT_H_
#define PLAYERAIRCRAFT_H_


#include "GameSprite.h"
#include "Entity.h"
#include "Aircraft.h"


class PlayerAircraft : public Aircraft
{
public:
    explicit PlayerAircraft();
    void update(float deltaTime) override;
    void collision(const Entity* other) override;
private:
    sf::Vector2f handleInput(float deltaTime);
};

#endif //PLAYERAIRCRAFT_H_
