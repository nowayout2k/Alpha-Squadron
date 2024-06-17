//
// Created by Johnnie Otis on 6/2/24.
//

#ifndef JET_H_
#define JET_H_


#include "GameSprite.h"
#include "Entity.h"
#include "Character.h"


class Jet : public Character
{
public:
    explicit Jet();
    void update(float deltaTime) override;
    void collision(const Entity* other) override;
private:
    sf::Vector2f handleInput(float deltaTime);
    void adjustOffsetToWindow(sf::Vector2f& offset);
};

#endif //JET_H_
