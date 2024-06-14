//
// Created by Johnnie Otis on 6/8/24.
//

#include "../Header/Projectile.h"
#include "../Header/Audio.h"
#include "../Header/Enemy.h"
#include "../Header/Player.h"
#include "../Header/Window.h"

Projectile::Projectile(Entity* owner, sf::Vector2f spawnPos, sf::Vector2f velocity) : m_velocity(velocity), m_owner(owner), SpriteEntity(true,
	"../Assets/Textures/AircraftSpriteSheet.png",
	sf::IntRect(376, 108, 10, 12))
{
	setScale(4.0f, 4.0f);
	setPosition(spawnPos);
	Audio::playSound(SoundEffectType::Shoot1, 10);
}

void Projectile::update(float deltaTime)
{
	sf::Vector2u windowSize = Window::getSize();
	move(m_velocity*deltaTime);
	auto position = getPosition();
	if(position.x > (float)windowSize.x || position.y > (float)windowSize.y || position.x <= 0 || position.y <= 0 || !m_owner)
		destroy();
}

void Projectile::collision(const Entity* other)
{
	if(!m_owner || m_owner->isDestroyPending())
		destroy();

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
