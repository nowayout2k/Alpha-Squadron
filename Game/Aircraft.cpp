#include "Aircraft.h"
#include "../Engine/Audio.h"
#include "../Engine/World.h"
#include "../Engine/Engine.h"

constexpr float DAMAGE_FLASH_TIME = 4.0f;
constexpr float DAMAGE_INVINCIBILITY_TIME = 0.3f;
constexpr float FIRE_COOLDOWN_TIME = 0.2f;
constexpr float MAX_SPAWN_DISTANCE = 1000.0f;

#ifndef M_PI
	#define M_PI 3.14159265359
#endif

#define MAX_HEALTH 120.f

Aircraft::Aircraft(const bool hasCollision, sf::Vector2f  scale, sf::Vector2f position)
	: GameSprite(hasCollision, false),
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

	auto healthDisplay = std::make_unique<GameText>(
		FontId::Gamer, "", 12, sf::Color::Black, sf::Text::Style::Regular, sf::Vector2f());
	m_healthDisplay = healthDisplay.get();
	attachNode(std::move(healthDisplay));
}

void Aircraft::changeHealth(float increment)
{
	m_health = std::min(m_health + increment, MAX_HEALTH);
	if(increment < 0)
	{
		if (m_isDamageAnimationActive || m_health <= 0)
		{
			Audio::playSound(SoundFxId::Explosion, 50);
			destroy();
			if(!(getNodeType() & static_cast<unsigned int>(NodeType::Player)))
				markForRemoval();
			return;
		}

		setColor(sf::Color::Red);
		Audio::playSound(SoundFxId::Damage, 50);
		m_timeSinceDamage = 0;
		m_isDamageAnimationActive = true;
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

void Aircraft::handleAnimation(float deltaTime)
{
	handleDamageAnimation(deltaTime);
}

bool Aircraft::isAllied() const
{
	return getNodeType() & static_cast<unsigned int>(NodeType::Player);
}

void Aircraft::checkProjectileLaunch(float dt, CommandQueue& commands)
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
		m_fireCooldownRemaining -= dt;
	}

	if (m_isLaunchingMissile)
	{
		commands.push(m_missileCommand);
		m_isLaunchingMissile = false;
	}
}

void Aircraft::handleDamageAnimation(float deltaTime)
{
	if (m_isDamageAnimationActive)
	{
		m_timeSinceDamage += deltaTime;

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

		//setCollision(m_timeSinceDamage > DAMAGE_INVINCIBILITY_TIME);
	}
}

void Aircraft::update(float deltaTime, CommandQueue& commands)
{
	Entity::update(deltaTime, commands);
	updateHealthDisplay();

	checkProjectileLaunch(deltaTime, commands);

	if (m_fireCooldownRemaining > 0)
		m_fireCooldownRemaining -= deltaTime;

	if (!(getNodeType() & static_cast<unsigned int>(NodeType::Player)))
	{
		updatePosition(deltaTime);
	}
}

void Aircraft::updateHealthDisplay()
{
	m_healthDisplay->setString(std::to_string((int)m_health) + " HP");
	auto bounds = GameSprite::getLocalBounds();
	m_healthDisplay->setPosition(bounds.width / 2, -bounds.height / 2);
	m_healthDisplay->setRotation(-getRotation());
}

void Aircraft::updatePosition(float deltaTime)
{
	auto& view = Engine::getWindow().getView();
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

void Aircraft::moveTowardsStart(float deltaTime)
{
	sf::Vector2f velocity = calculateDirectionalVelocity(m_enterDirection);
	setVelocity(velocity);
	m_spawnDistanceTravelled += getMaxSpeed() * deltaTime;
}

void Aircraft::exitPhase()
{
	sf::Vector2f velocity = calculateDirectionalVelocity(m_exitDirection);
	setVelocity(velocity);
}

void Aircraft::followAiRoutines(float deltaTime)
{
	float distanceToTravel = m_aiRoutines[m_routineIndex].distance;
	if (m_routineDistanceTravelled > distanceToTravel)
	{
		m_routineIndex = (m_routineIndex + 1) % m_aiRoutines.size();
		m_routineDistanceTravelled = 0.0f;
	}

	float radians = Utility::toRadian(m_aiRoutines[m_routineIndex].angle);
	sf::Vector2f velocity = sf::Vector2f(
		World::getScrollSpeed() + getMaxSpeed() * std::cos(radians),
		getMaxSpeed() * std::sin(radians));

	setVelocity(velocity);
	m_routineDistanceTravelled += getMaxSpeed() * deltaTime;
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
	for (const auto& data : World::GameData.AircraftData)
	{
		if (data.second.Type == getAircraftType())
		{
			if(getNodeType() & static_cast<unsigned int>(NodeType::Player))
			{
				m_health = 100;
			}
			else
			{
				m_health = data.second.Health;
			}
			m_speed = data.second.Speed;
			m_aiRoutines = data.second.AiRoutines;
			m_despawnDistance = data.second.DespawnDistance;
			m_enterDirection = data.second.EnterDirection;
			m_exitDirection = data.second.ExitDirection;
			setTextureId(data.second.TextureId);
			setTextureLoadArea(data.second.TextureLoadArea);
		}
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

	m_fireCommand.NodeType = (unsigned int)NodeType::CollisionLayer;
	m_fireCommand.Action =
		[this] (WorldNode& node, float dt)
		{
		  createBullets(node);
		};
	m_missileCommand.NodeType = (unsigned int)NodeType::CollisionLayer;
	m_missileCommand.Action =
		[this] (WorldNode& node, float delta)
		{
		  createProjectile(node, ProjectileType::Missile, 0.f, 0.5f);
		};

	m_healthDisplay->setScale(getScale().x < 0 ? -1 : 1, 1);
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
	projectile->setScale(4, 4);
	sf::Vector2f offset(sign * getBoundingRect().width + sign * xOffset, getScale().y * (yOffset + getGlobalBounds().height/2));
	projectile->setPosition(getWorldPosition() + offset);
	if(!isAllied())
		projectile->setRotation(180);
	projectile->loadResources();
	node.attachNode(std::move(projectile));
}
