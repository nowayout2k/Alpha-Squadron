//
// Created by Johnnie Otis on 6/8/24.
//

#include "Projectile.h"
#include "Audio.h"
#include "Engine.h"

Projectile::Projectile(NodeType owner, sf::Vector2f spawnPos, sf::Vector2f velocity) : m_ownerType(owner),
	GameSprite(true,
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

	sf::Vector2u windowSize = Engine::getWindow().getSize();
	auto position = getPosition();
	if(position.x > (float)windowSize.x || position.y > (float)windowSize.y || position.x <= 0 || position.y <= 0 || m_ownerType == NodeType::None)
		destroy();
}


void Projectile::render(sf::RenderTarget& renderTarget, sf::RenderStates states) const
{
	GameSprite::render(renderTarget, states);
}

void Projectile::collision(const Entity* other)
{
	GameSprite::collision(other);

	if(m_ownerType == NodeType::None || ((other->getNodeType() & (unsigned int)NodeType::Player) > 0 && m_ownerType != NodeType::Player) ||
		((other->getNodeType() & (unsigned int)NodeType::Enemy) > 0 && m_ownerType != NodeType::Enemy))
	{
		destroy();
	}
}
