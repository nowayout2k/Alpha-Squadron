// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file Projectile.cpp
 * @brief Implements the Projectile class methods.
 *
 * This source file provides the implementation for the Projectile class,
 * handling launch timing, guided movement, linear motion, rendering, and resource loading.
 */

#include "../Headers/Projectile.h"
#include "../Headers/Audio.h"
#include "../Headers/Engine.h"
#include "../Headers/EmitterNode.h"

#define LAUNCH_TIME 0.25f ///< Duration (in seconds) for the projectile's launch phase.

Projectile::Projectile(NodeType type, ProjectileType projectileType, sf::Vector2f targetDirection, sf::Vector2f launchDirection)
	: m_type(type),
	  m_targetDirection(targetDirection),
	  m_launchDirection(launchDirection),
	  m_timeSinceLaunch(0),
	  m_maxSpeed(100),
	  m_isLaunching(true),
	  m_projectileType(projectileType),
	  GameSprite(true, false, sf::IntRect())
{
	// Constructor initializes projectile parameters including launch state and direction.
}

void Projectile::update(sf::Time deltaTime, CommandQueue& commands)
{
	// Update launch timer if projectile is still launching.
	if(m_isLaunching)
	{
		m_timeSinceLaunch += deltaTime.asSeconds();
		if(m_timeSinceLaunch > LAUNCH_TIME)
		{
			m_isLaunching = false;
		}
	}

	// For guided projectiles (e.g., missiles) that are not launching, adjust trajectory.
	if (isGuided() && !m_isLaunching)
	{
		const float approachRate = getMaxSpeed() + World::getScrollSpeed();
		const float turnRadius = 300.0f; // Maximum turn angle in degrees per second

		// Calculate desired velocity vector in the target direction.
		sf::Vector2f desiredVelocity = Utility::unitVector(m_targetDirection) * approachRate;

		// Determine current and target angles of velocity.
		float currentAngle = std::atan2(getVelocity().y, getVelocity().x);
		float targetAngle = std::atan2(desiredVelocity.y, desiredVelocity.x);

		// Compute the smallest angle difference, considering wrap-around.
		float angleDifference = targetAngle - currentAngle;
		if (angleDifference > M_PI) angleDifference -= 2 * M_PI;
		if (angleDifference < -M_PI) angleDifference += 2 * M_PI;

		// Clamp the angle change based on the maximum allowed turn rate.
		float maxAngleChange = turnRadius * deltaTime.asSeconds() * (M_PI / 180.0f);
		float angleToApply = std::clamp(angleDifference, -maxAngleChange, maxAngleChange);

		// Compute the new velocity angle.
		float newAngle = currentAngle + angleToApply;

		sf::Vector2f newVelocity;
		newVelocity.x = std::cos(newAngle) * approachRate;
		newVelocity.y = std::sin(newAngle) * approachRate;

		// Update projectile's rotation and velocity.
		setRotation(Utility::toDegree(newAngle));
		setVelocity(newVelocity);
	}
	else
	{
		// For non-guided projectiles, maintain constant velocity in the launch direction.
		setVelocity(m_launchDirection.x * (getMaxSpeed() + World::getScrollSpeed()), 0);
	}

	// Update the base class to ensure proper sprite behavior.
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
		// Set the target direction to the unit vector from the projectile's current position to the target position.
		m_targetDirection = Utility::unitVector(position - getWorldPosition());
	}
}

float Projectile::getDamage()
{
	return 25;
}

void Projectile::loadResources()
{
	// Retrieve projectile configuration data based on its type.
	auto dataPair = World::GameData.ProjectileData.find(m_projectileType);
	if (dataPair != World::GameData.ProjectileData.end())
	{
		auto data = dataPair->second;
		m_maxSpeed = data.MaxSpeed;
		setTextureId(data.TextureId);
		setTextureLoadArea(data.TextureLoadArea);
	}

	// Load resources defined in the base GameSprite.
	GameSprite::loadResources();
	// Set the origin for proper rotation and movement.
	setOrigin(0, 0.5f);

	// For guided projectiles, attach emitter nodes for smoke and propellant effects.
	if(isGuided())
	{
		auto rect = getBoundingRect();
		std::unique_ptr<EmitterNode> smoke(new EmitterNode(Particle::Smoke));
		smoke->setOrigin(0, 0.5f);
		smoke->setPosition(0.f, rect.height/2);
		attachNode(std::move(smoke));

		std::unique_ptr<EmitterNode> propellant(new EmitterNode(Particle::Propellant));
		propellant->setOrigin(0, 0.5f);
		propellant->setPosition(0.f, rect.height/2);
		attachNode(std::move(propellant));
	}
}
