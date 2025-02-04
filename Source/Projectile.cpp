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
	m_maxSpeed(100),
	m_isLaunching(true),
	m_projectileType(projectileType),
	GameSprite(true,false,sf::IntRect())
{
	setScale(1.0f, 1.0f);
	Audio::playSound(SoundFxId::BulletLaunch, 10);
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
	return m_maxSpeed;
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

int Projectile::getDamage()
{
	return 25;
}

void Projectile::loadResources()
{
	auto dataPair = World::GameData.ProjectileData.find(m_projectileType);

	if (dataPair != World::GameData.ProjectileData.end())
	{
		auto data = dataPair->second;
		m_maxSpeed = data.MaxSpeed;
		setTextureId(data.TextureId);
		setTextureLoadArea(data.TextureLoadArea);
	}

	GameSprite::loadResources();
}
