//
// Created by Johnnie Otis on 6/2/24.
//

#ifndef ALPHA_SQUADRON_HEADER_PLAYER_H_
#define ALPHA_SQUADRON_HEADER_PLAYER_H_


#include "SpriteEntity.h"
#include "Entity.h"

class Player : public SpriteEntity
{
public:
    explicit Player();
    void update(float deltaTime) override;
    void collision(const Entity* other) override;
private:
    sf::Vector2f handleInput(float deltaTime);
    void adjustOffsetToWindow(sf::Vector2f& offset);
	void startDamageAnimation();
	void handleAnimation(float deltaTime, sf::Vector2f offset);
	void updateColor(float deltaTime);
	void fireBullet(sf::Vector2f offset);

	const float DAMAGE_FLASH_TIME = 4.0f;
	const float DAMAGE_INVINCIBILITY_TIME = .3f;

	float m_timeSinceDamage;
	bool m_isBeingDamaged;
	int m_health;
	float m_fireCooldownRemaining = 0;
	const float FIRE_COOLDOWN_TIME = 0.5f;
};


#endif //ALPHA_SQUADRON_HEADER_PLAYER_H_
