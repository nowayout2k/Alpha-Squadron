//
// Created by Johnnie Otis on 6/1/24.
//

#ifndef ENEMYAIRCRAFT_H_
#define ENEMYAIRCRAFT_H_

#include "GameSprite.h"
#include "Entity.h"
#include "Aircraft.h"

class EnemyAircraft : public Aircraft
{
public:
	explicit EnemyAircraft(bool hasCollision, sf::Vector2f position);
    void update(float deltaTime) override;
    void collision(const Entity* other) override;
private:
    sf::Texture m_texture;
};

#endif //ENEMYAIRCRAFT_H_
