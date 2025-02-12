// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Projectile.h"
#include "../Headers/Audio.h"
#include "../Headers/Engine.h"
#include "../Headers/EmitterNode.h"

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
}

void Projectile::update(sf::Time deltaTime, CommandQueue& commands)
{
	if(m_isLaunching)
	{
		m_timeSinceLaunch += deltaTime.asSeconds();
		if(m_timeSinceLaunch > LAUNCH_TIME)
		{
			m_isLaunching = false;
		}
	}

	if (isGuided() && !m_isLaunching)
	{
		const float approachRate = getMaxSpeed() + World::getScrollSpeed();
		const float turnRadius = 300.0f; // Maximum turn angle in degrees per second

		sf::Vector2f desiredVelocity = Utility::unitVector(m_targetDirection) * approachRate;

		float currentAngle = std::atan2(getVelocity().y, getVelocity().x);
		float targetAngle = std::atan2(desiredVelocity.y, desiredVelocity.x);

		float angleDifference = targetAngle - currentAngle;
		if (angleDifference > M_PI) angleDifference -= 2 * M_PI;  // Wrap around
		if (angleDifference < -M_PI) angleDifference += 2 * M_PI;

		float maxAngleChange = turnRadius * deltaTime.asSeconds() * (M_PI / 180.0f);
		float angleToApply = std::clamp(angleDifference, -maxAngleChange, maxAngleChange);

		float newAngle = currentAngle + angleToApply;

		sf::Vector2f newVelocity;
		newVelocity.x = std::cos(newAngle) * approachRate;
		newVelocity.y = std::sin(newAngle) * approachRate;

		setRotation(Utility::toDegree(newAngle));

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

float Projectile::getDamage()
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
	setOrigin(0, 0.5f);
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
