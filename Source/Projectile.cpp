//
// Created by Johnnie Otis on 6/8/24.
//

#include "../Header/Projectile.h"
#include "../Header/Audio.h"
#include "../Header/EnemyAircraft.h"
#include "../Header/PlayerAircraft.h"
#include "../Header/Game.h"

Projectile::Projectile(Entity* owner, sf::Vector2f spawnPos, sf::Vector2f velocity) : m_velocity(velocity), m_owner(owner),
	GameSprite(EntityType::Projectile, true,
	TextureId::AircraftSpriteSheet,
	sf::IntRect(376, 108, 10, 12))
{
	m_sprite.setScale(4.0f, 4.0f);
	m_sprite.setPosition(spawnPos);
	Audio::playSound(SoundFxId::Shoot1, 10);
}

void Projectile::update(float deltaTime)
{
	sf::Vector2u windowSize = Game::getWindowSize();
	m_sprite.move(m_velocity*deltaTime);
	auto position = m_sprite.getPosition();
	if(position.x > (float)windowSize.x || position.y > (float)windowSize.y || position.x <= 0 || position.y <= 0 || !m_owner)
		destroy();
}

void Projectile::collision(const Entity* other)
{
	GameSprite::collision(other);

	if(!m_owner || m_owner->isDestroyPending())
		destroy();

	auto enemy = dynamic_cast<const EnemyAircraft*>(other);
	auto player = dynamic_cast<const PlayerAircraft*>(other);

	auto enemyOwner = dynamic_cast<const EnemyAircraft*>(m_owner);
	auto playerOwner= dynamic_cast<const PlayerAircraft*>(m_owner);

	if(player && !playerOwner || enemy && !enemyOwner)
	{
		destroy();
	}
}
