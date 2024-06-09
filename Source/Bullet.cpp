//
// Created by Johnnie Otis on 6/8/24.
//

#include "../Header/Bullet.h"
#include "../Header/AudioManager.h"
#include "../Header/Enemy.h"
#include "../Header/Player.h"

Bullet::Bullet(Entity* owner, sf::Vector2f spawnPos, sf::Vector2f velocity) : m_velocity(velocity), m_owner(owner), SpriteEntity(true,
	"../Assets/Textures/AircraftSpriteSheet.png",
	sf::IntRect(376, 108, 10, 12))
{
	setScale(2.0f, 2.0f);
	setPosition(spawnPos);
	m_hasCollision = true;
	AudioManager::playSound(SoundEffectType::Collect, 10);
}

void Bullet::update(float deltaTime)
{
	sf::Vector2u windowSize = WindowManager::getSize();
	move(m_velocity*deltaTime);
	auto position = getPosition();
	if(position.x > windowSize.x || position.y > windowSize.y || position.x <= 0 || position.y <= 0)
		destroy();
}

void Bullet::collision(const Entity* other)
{
	SpriteEntity::collision(other);
	auto enemy = dynamic_cast<const Enemy*>(other);
	auto player = dynamic_cast<const Player*>(other);

	auto enemyOwner = dynamic_cast<const Enemy*>(m_owner);
	auto playerOwner= dynamic_cast<const Player*>(m_owner);

	if(player && !playerOwner || enemy && !enemyOwner)
	{
		destroy();
	}
}
