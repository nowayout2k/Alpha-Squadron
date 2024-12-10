//
// Created by Johnnie Otis on 6/8/24.
//

#include "Projectile.h"
#include "Audio.h"
#include "Engine.h"

Projectile::Projectile(NodeType ownerType, Projectile::Type projectileType) :
	GameSprite(true,
	TextureId::AircraftSpriteSheet,
	sf::IntRect(376, 108, 10, 12))
{
	setScale(1.0f, 1.0f);
	Audio::playSound(SoundFxId::Shoot1, 10);
	m_ownerType = ownerType;
	m_projectileType = projectileType;
}

void Projectile::update(float deltaTime, CommandQueue& commands)
{
	GameSprite::update(deltaTime, commands);

	if (isGuided())
	{
		const float approachRate = 200.f;
		sf::Vector2f newVelocity = Utility::unitVector(approachRate * deltaTime * m_targetDirection + getVelocity());
		newVelocity *= getMaxSpeed();
		float angle = std::atan2(newVelocity.y, newVelocity.x);
		setRotation(Utility::toDegree(angle) + 180.f);
		setVelocity(newVelocity);
	}
}

void Projectile::render(sf::RenderTarget& renderTarget, sf::RenderStates states) const
{
	GameSprite::render(renderTarget, states);
}

bool Projectile::isGuided() const
{
	return m_projectileType == Missile;
}

void Projectile::guideTowards(sf::Vector2f position)
{
	if(isGuided())
		m_targetDirection = Utility::unitVector(position - getWorldPosition());
}

void Projectile::collision(const Entity* other)
{
	GameSprite::collision(other);
}

sf::FloatRect Projectile::getBoundingRect() const
{
	return getWorldTransform().transformRect(getGlobalBounds());
}

float Projectile::getMaxSpeed() const
{
	return 900.0f;
}
