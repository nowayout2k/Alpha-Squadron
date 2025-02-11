// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include "../Headers/Aircraft.h"
#include "../Headers/Audio.h"
#include "../Headers/World.h"
#include "../Headers/Engine.h"

constexpr float DAMAGE_FLASH_TIME = 2.0f;
constexpr float DAMAGE_INVINCIBILITY_TIME = 0.5f;
constexpr float MAX_SPAWN_DISTANCE = 1000.0f;

#ifndef M_PI
	#define M_PI 3.14159265359
#endif

#define MAX_HEALTH 100.f

Aircraft::Aircraft(const bool hasCollision, sf::Vector2f  scale, sf::Vector2f position)
	: m_explosion(ResourceManager::loadResource(TextureId::ExplosionSpriteSheet), sf::Vector2i(256, 256), 16, sf::seconds(1)),
	  m_showExplosion(false),
	GameSprite(hasCollision, true),
		m_isExiting(false),
		m_timeSinceDamage(0),
		m_routineDistanceTravelled(0),
		m_spawnDistanceTravelled(0),
		m_routineIndex(0),
		m_isDamageAnimationActive(false),
		m_fireCooldownRemaining(0),
		m_spawnPos(position),
		m_isFiring(false),
		m_fireCommand(),
		m_missileCommand(),
		m_fireRateLevel(0),
		m_isLaunchingMissile(false),
		m_spreadLevel(0),
	  	m_missileCount(3)
{
	setScale(scale);
	setPosition(m_spawnPos);
	m_explosion.setOrigin(m_explosion.getFrameSize().x / 2.f, m_explosion.getFrameSize().y / 2.f);

}

void Aircraft::changeHealth(float increment)
{
	m_health = std::min(m_health + increment, MAX_HEALTH);
	if(increment < 0)
	{
		if (((getNodeType() & static_cast<unsigned int>(NodeType::Player)) && m_isDamageAnimationActive) || m_health <= 0)
		{
			m_health=0;
			Audio::playSound(SoundFxId::Explosion, 50);
        	destroy();
			m_showExplosion = true;
			return;
		}

		Audio::playSound(SoundFxId::TakeDamage, 50);
		if((getNodeType() & static_cast<unsigned int>(NodeType::Player)))
			Audio::playSound(SoundFxId::DamageWarning1, 20);
		m_timeSinceDamage = 0;
		m_isDamageAnimationActive = true;
		setIsCollidable(false);
	}
}

void Aircraft::fire()
{
 	m_isFiring = true;
}

void Aircraft::launchMissile()
{
	if(m_missileCount > 0)
	{
		m_missileCount--;
		m_isLaunchingMissile = true;
	}
}

void Aircraft::updateRollAnimation()
{
	sf::IntRect textureRect = World::GameData.AircraftData[getAircraftType()].SpriteTextureRegion;
	if (getVelocity().y > 0.f)
		textureRect.left += textureRect.width;
	else if (getVelocity().y < 0.f)
		textureRect.left += 2 * textureRect.width;
	setSpriteTextureRegion(textureRect);
}

void Aircraft::handleAnimation(sf::Time deltaTime)
{
	handleDamageAnimation(deltaTime);
}

bool Aircraft::isAllied() const
{
	return getNodeType() & static_cast<unsigned int>(NodeType::Player);
}

void Aircraft::checkProjectileLaunch(sf::Time dt, CommandQueue& commands)
{
	if (!isAllied())
	{
		fire();
	}

	if (m_isFiring && m_fireCooldownRemaining <= 0)
	{
		commands.push(m_fireCommand);
		m_fireCooldownRemaining += 1.f / (m_fireRateLevel+1);
		m_isFiring = false;
	}
	else if (m_fireCooldownRemaining > 0)
	{
		m_fireCooldownRemaining -= dt.asSeconds();
	}

	if (m_isLaunchingMissile)
	{
		commands.push(m_missileCommand);
		m_isLaunchingMissile = false;
	}
}

void Aircraft::handleDamageAnimation(sf::Time deltaTime)
{
	if (m_isDamageAnimationActive)
	{
		m_timeSinceDamage += deltaTime.asSeconds();

		if (m_timeSinceDamage > DAMAGE_FLASH_TIME)
		{
			setColor(sf::Color::White);
			m_isDamageAnimationActive = false;
		}
		else
		{
			float phase = fmod(m_timeSinceDamage, 1.0f);
			float t = 0.5f * (1.0f + std::cos(phase * 2.0f * M_PI));
			float c = Utility::lerp(0, 255, t);
			setColor(sf::Color(255, c, c, 255));
		}
	}
}

void Aircraft::update(sf::Time deltaTime, CommandQueue& commands)
{
	if (isDestroyed())
	{
		if(m_explosion.isComplete())
			markForRemoval();
		else
			m_explosion.update(deltaTime);
		return;
	}

	GameSprite::update(deltaTime, commands);

	if(m_timeSinceDamage > DAMAGE_INVINCIBILITY_TIME)
	{
		setIsCollidable(true);
	}
	else
	{
		m_timeSinceDamage += deltaTime.asSeconds();
	}

	checkProjectileLaunch(deltaTime, commands);

	if (m_fireCooldownRemaining > 0)
		m_fireCooldownRemaining -= deltaTime.asSeconds();

	if (!(getNodeType() & static_cast<unsigned int>(NodeType::Player)))
	{
		updateAiPosition(deltaTime);
	}

	updateRollAnimation();
}

void Aircraft::updateAiPosition(sf::Time deltaTime)
{
	auto& view = World::getWorldView();
	sf::Vector2f viewSize = view.getSize();
	sf::Vector2f viewCenter = view.getCenter();
	auto viewRect = sf::FloatRect(viewCenter - viewSize / 2.f, viewSize);

	if (viewRect.left + viewRect.width > m_spawnPos.x + m_despawnDistance)
		m_isExiting = true;

	if (m_spawnDistanceTravelled < MAX_SPAWN_DISTANCE)
	{
		moveTowardsStart(deltaTime);
	}
	else if (m_isExiting)
	{
		exitPhase();
	}
	else if (!m_aiRoutines.empty())
	{
		followAiRoutines(deltaTime);
	}
}

void Aircraft::moveTowardsStart(sf::Time deltaTime)
{
	sf::Vector2f velocity = calculateDirectionalVelocity(m_enterDirection);
	setVelocity(velocity);
	m_spawnDistanceTravelled += getMaxSpeed() * deltaTime.asSeconds();
}

void Aircraft::exitPhase()
{
	sf::Vector2f velocity = calculateDirectionalVelocity(m_exitDirection);
	setVelocity(velocity);
}

void Aircraft::followAiRoutines(sf::Time deltaTime)
{
	float distanceToTravel = m_aiRoutines[m_routineIndex].distance;
	if (m_routineDistanceTravelled > distanceToTravel)
	{
		m_routineIndex = (m_routineIndex + 1) % m_aiRoutines.size();
		m_routineDistanceTravelled = 0.0f;
	}

	float radians = Utility::toRadian(m_aiRoutines[m_routineIndex].angle);
	sf::Vector2f velocity = sf::Vector2f(World::getScrollSpeed() + getMaxSpeed() * std::cos(radians), getMaxSpeed() * std::sin(radians));

	setVelocity(velocity);
	m_routineDistanceTravelled += getMaxSpeed() * deltaTime.asSeconds();
}

sf::Vector2f Aircraft::calculateDirectionalVelocity(Direction direction) const
{
	switch (direction)
	{
	case Direction::North:
		return {0, -getMaxSpeed()};
	case Direction::South:
		return {0, getMaxSpeed()};
	case Direction::East:
		return { getMaxSpeed() + World::getScrollSpeed(), 0};
	case Direction::West:
		return {-(getMaxSpeed() - World::getScrollSpeed()), 0};
	default:
		return {0, 0};
	}
}

void Aircraft::loadResources()
{
	auto dataPair = World::GameData.AircraftData.find(getAircraftType());

	if (dataPair != World::GameData.AircraftData.end())
	{
		auto data = dataPair->second;
		if(getNodeType() & static_cast<unsigned int>(NodeType::Player))
		{
			m_health = 100;
		}
		else
		{
			m_health = data.Health;
		}
		m_speed = data.Speed;
		m_aiRoutines = data.AiRoutines;
		m_despawnDistance = data.DespawnDistance;
		m_enterDirection = data.EnterDirection;
		m_exitDirection = data.ExitDirection;
		setTextureId(data.TextureId);
		setTextureLoadArea(data.TextureLoadArea);
		setSpriteTextureRegion(data.SpriteTextureRegion);
	}

	GameSprite::loadResources();

	if (!(getNodeType() & static_cast<unsigned int>(NodeType::Player)))
	{
		float vx = 0;
		float vy = 0;
		switch (m_enterDirection)
		{
		case Direction::North:
			vx = -1000;
			vy = -1000;
			break;
		case Direction::South:
			vx = -1000;
			vy = 1000;
			break;
		case Direction::East:
			vx = -2100;
			vy = 500;
			break;
		case Direction::West:
			vx = 0;
			vy = 500;
			break;
		case Direction::DirectionCount:
		default:
			vx = 0;
			vy = 0;
			break;
		}
		m_spawnPos = m_spawnPos + sf::Vector2f(vx, vy);
		setPosition(m_spawnPos);
	}

	m_fireCommand.NodeType = (unsigned int)NodeType::SpriteFrontLayer;
	m_fireCommand.Action =
		[this] (WorldNode& node, sf::Time dt)
		{
		  createBullets(node);
		};
	m_missileCommand.NodeType = (unsigned int)NodeType::SpriteFrontLayer;
	m_missileCommand.Action =
		[this] (WorldNode& node, sf::Time delta)
		{
		  createProjectile(node, ProjectileType::Missile, 0.f, 0.5f);
		};
}

void Aircraft::createBullets(WorldNode& node)
{
	switch (m_spreadLevel)
	{
	case 0:
		createProjectile(node, ProjectileType::Bullet, 0.0f, 0.0f);
		break;
	case 1:
		createProjectile(node, ProjectileType::Bullet, -0.33f, 0.33f);
		createProjectile(node, ProjectileType::Bullet, +0.33f, 0.33f);
		break;
	case 2:
		createProjectile(node, ProjectileType::Bullet, -0.5f, 0.33f);
		createProjectile(node, ProjectileType::Bullet, 0.0f, 0.0f);
		createProjectile(node, ProjectileType::Bullet, +0.5f, 0.33f);
		break;
	}
}

void Aircraft::createProjectile(WorldNode& node, ProjectileType projectileType, float xOffset, float yOffset)
{
	float sign = isAllied() ? 1.f : - 1.f;
	std::unique_ptr<Projectile> projectile(new Projectile(isAllied() ? NodeType::AlliedProjectile :  NodeType::EnemyProjectile ,projectileType, sf::Vector2f(0, 0), sf::Vector2f(sign, 0)));

	if(projectileType == ProjectileType::Missile)
		projectile->setScale(.75, .75);
	else
		projectile->setScale(1, 1);

	if(!isAllied())
		projectile->setRotation(180);

	projectile->loadResources();

	sf::Vector2f offset(sign * (getBoundingRect().width/2) + (sign * xOffset), projectileType == ProjectileType::Missile ? getBoundingRect().height/2 : 0);
	projectile->setPosition(getWorldPosition() + offset);

	node.attachNode(std::move(projectile));
}

void Aircraft::render(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isDestroyed() && m_showExplosion)
		target.draw(m_explosion, states);
	else
		GameSprite::render(target, states);
}
