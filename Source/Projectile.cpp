// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Projectile.h"
#include "../Headers/Audio.h"
#include "../Headers/Engine.h"

#define LAUNCH_TIME 0.25f

Projectile::Projectile(NodeType type, ProjectileType projectileType, sf::Vector2f targetDirection, sf::Vector2f launchDirection) :
	m_type(type),
	m_targetDirection(targetDirection),
	m_launchDirection(launchDirection),
	m_timeSinceLaunch(0),
	m_isLaunching(true),
	m_projectileType(projectileType),
	GameSprite(true,
		projectileType == Missile ? TextureId::EnemiesSpriteSheet : TextureId::AircraftSpriteSheet, false,
		projectileType == Missile ? sf::IntRect(211, 213, 7, 7) : sf::IntRect(376, 108, 5, 4))
{
	setScale(1.0f, 1.0f);
	Audio::playSound(SoundFxId::Shoot1, 10);
}

void Projectile::update(float deltaTime, CommandQueue& commands)
{
	if(m_isLaunching)
	{
		m_timeSinceLaunch += deltaTime;
		if(m_timeSinceLaunch > LAUNCH_TIME)
		{
			m_isLaunching = false;
		}
	}

	if (isGuided() && !m_isLaunching)
	{

		const float approachRate = getMaxSpeed() + World::getScrollSpeed();
		const float turnRate = 10.0f; // Controls how fast it turns

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
		setVelocity(m_launchDirection.x * (getMaxSpeed() + World::getScrollSpeed()), 0);
	}

	GameSprite::update(deltaTime, commands);
}

float Projectile::getMaxSpeed() const
{
	auto data = World::GameData.ProjectileData;
	auto it = data.find(m_projectileType);
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

int Projectile::getDamage() const
{
	return 25;
}
