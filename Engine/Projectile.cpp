//
// Created by Johnnie Otis on 6/8/24.
//

#include "Projectile.h"
#include "Audio.h"
#include "Engine.h"

Projectile::Projectile(ProjectileType projectileType, sf::Vector2f targetDirection) : m_targetDirection(targetDirection),
	GameSprite(true,
		projectileType == Missile ? TextureId::EnemiesSpriteSheet : TextureId::AircraftSpriteSheet,
		projectileType == Missile ? sf::IntRect(211, 213, 7, 9) : sf::IntRect(376, 108, 10, 12))
{
	setScale(1.0f, 1.0f);
	Audio::playSound(SoundFxId::Shoot1, 10);
	m_projectileType = projectileType;
}

void Projectile::update(float deltaTime, CommandQueue& commands)
{
	if (isGuided())
	{

		const float approachRate = getMaxSpeed() + World::getScrollSpeed();
		const float turnRate = 5.0f; // Controls how fast it turns

		// Compute the desired velocity (toward target)
		sf::Vector2f desiredVelocity = Utility::unitVector(m_targetDirection) * approachRate;

		// Interpolate velocity towards the desired direction
		sf::Vector2f newVelocity = getVelocity() + (desiredVelocity - getVelocity()) * (turnRate * deltaTime);

		// Ensure the missile moves at max speed
		newVelocity = Utility::unitVector(newVelocity) * approachRate;

		// Update missile rotation
		float angle = std::atan2(newVelocity.y, newVelocity.x);
		setRotation(Utility::toDegree(angle));

		// Apply new velocity
		setVelocity(newVelocity);
	}
	else
	{
		setVelocity(m_targetDirection.x * (getMaxSpeed() + World::getScrollSpeed()), 0);
	}

	GameSprite::update(deltaTime, commands);
}

float Projectile::getMaxSpeed() const
{
	auto data = World::GameData.ProjectileData;
	auto it = data.find(Utility::projectileTypeToString(m_projectileType));
	if(it == data.end())
	{
		return 100.0f;
	}

	return it->second.Value;
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
	{
		m_targetDirection = Utility::unitVector(position - getWorldPosition());
	}
}

void Projectile::collision(const Entity* other)
{
	GameSprite::collision(other);
}

sf::FloatRect Projectile::getBoundingRect() const
{
	return getWorldTransform().transformRect(getGlobalBounds());
}

int Projectile::getDamage() const
{
	return 0;
}
