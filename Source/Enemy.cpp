//
// Created by Johnnie Otis on 6/1/24.
//

#include "../Header/Enemy.h"
#include "../Header/Player.h"

Enemy::Enemy(bool hasCollision, sf::Vector2f position) : SpriteEntity(hasCollision, "../Assets/Textures/EnemiesSpriteSheet.png",
                                               sf::IntRect(70, 200, 25, 12))
{
    setScale(sf::Vector2f(-2,2));
    setPosition(position);
	m_health = 100;
}

bool goUp = false;
void Enemy::update(float deltaTime)
{
	if(m_health == 0)
	{
		m_isAlive = false;
		return;
	}

	Entity::update(deltaTime);
	auto windowSize = WindowManager::getSize();
	if(goUp)
	{
		if(getPosition().y <= 0)
			goUp = false;
		move(sf::Vector2f(0, -100*deltaTime));
	}
	else
	{
		if(getPosition().y >= windowSize.y)
			goUp = true;
		move(sf::Vector2f(0, 100*deltaTime));
	}
}

void Enemy::collision(const Entity* other)
{
	SpriteEntity::collision(other);
    const Player* player = dynamic_cast<const Player*>(other);
    if (player && player->hasCollision())
        m_health-=100;
}
