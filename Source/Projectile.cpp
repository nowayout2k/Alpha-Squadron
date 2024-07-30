//
// Created by Johnnie Otis on 6/8/24.
//

#include "../Header/Projectile.h"
#include "../Header/Audio.h"
#include "../Header/EnemyAircraft.h"
#include "../Header/PlayerAircraft.h"
#include "../Header/Game.h"

Projectile::Projectile(EntityType owner, sf::Vector2f spawnPos, sf::Vector2f velocity) : m_ownerType(owner),
	GameSprite(EntityType::Projectile, true,
	TextureId::AircraftSpriteSheet,
	sf::IntRect(376, 108, 10, 12))
{
	setVelocity(velocity);
	setScale(1.0f, 1.0f);
	setPosition(spawnPos);
	Audio::playSound(SoundFxId::Shoot1, 10);
}

void Projectile::update(float deltaTime)
{
	GameSprite::update(deltaTime);

	/*sf::Vector2u windowSize = World::getView();
	auto position = getPosition();
	if(position.x > (float)windowSize.x || position.y > (float)windowSize.y || position.x <= 0 || position.y <= 0 || m_ownerType == EntityType::None)
		destroy();*/
}

void Projectile::render(sf::RenderTarget& renderTarget, sf::RenderStates states) const
{
	GameSprite::render(renderTarget, states);
}

void Projectile::collision(const Entity* other)
{
	GameSprite::collision(other);

	if(m_ownerType == EntityType::None || (other->getEntityType() == EntityType::Player && m_ownerType != EntityType::Player) ||
		(other->getEntityType() == EntityType::Enemy && m_ownerType != EntityType::Enemy))
	{
		destroy();
	}
}
