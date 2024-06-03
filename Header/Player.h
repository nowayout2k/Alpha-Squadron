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
	void startDamageAnimation();
	void handleAnimation(float deltaTime, sf::Vector2f offset);
	const float DAMAGE_FLASH_TIME = 4.0f;
	const float DAMAGE_INVINCIBILITY_TIME = 1.0f;
	float m_timeSinceDamage = 0;
	bool m_isBeingDamaged = false;
};


#endif //ALPHA_SQUADRON_HEADER_PLAYER_H_
