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

std::vector<AircraftData> Aircraft::m_aircraftData = LoadAircraftData("../Game/DataFiles/aircraftData.json");

Aircraft::Aircraft(const bool hasCollision, sf::Vector2f scale, sf::Vector2f position)
	: GameSprite(hasCollision),
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
		m_spreadLevel(0)
{
	setScale(scale);
	setPosition(m_spawnPos);

	auto healthDisplay = std::make_unique<GameText>(
		FontId::Gamer, "", 12, sf::Color::Black, sf::Text::Style::Regular, sf::Vector2f());
	m_healthDisplay = healthDisplay.get();
	attachNode(std::move(healthDisplay));
}

void Aircraft::takeDamage(int health)
{
	m_health -= health;
	if (m_isDamageAnimationActive || m_health <= 0)
	{
		Audio::playSound(SoundFxId::Explosion, 50);
		destroy();
		return;
	}

	setColor(sf::Color::Red);
	Audio::playSound(SoundFxId::Damage, 50);
	m_timeSinceDamage = 0;
	m_isDamageAnimationActive = true;
}

void Aircraft::fire()
{
 	m_isFiring = true;
}

void Aircraft::launchMissile()
{
	m_isLaunchingMissile = true;
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

void Aircraft::createBullets()
{
	switch (m_spreadLevel)
	{
	case 0:
		createProjectile(Projectile::Bullet, 0.0f, 0.5f);
		break;
	case 1:
		createProjectile(Projectile::Bullet, -0.33f, 0.33f);
		createProjectile(Projectile::Bullet, +0.33f, 0.33f);
		break;
	case 2:
		createProjectile(Projectile::Bullet, -0.5f, 0.33f);
		createProjectile(Projectile::Bullet, 0.0f, 0.5f);
		createProjectile(Projectile::Bullet, +0.5f, 0.33f);
		break;
	}
}

void Aircraft::createProjectile(Projectile::Type projectileType, float xOffset, float yOffset)
{
	auto nodeType = isAllied() ? NodeType::Player : NodeType::Enemy;
	std::unique_ptr<Projectile> projectile(new Projectile(nodeType, projectileType));
	sf::Vector2f offset(getGlobalBounds().width/2 + xOffset,yOffset * getGlobalBounds().height/2);
	projectile->setPosition(offset);
	projectile->setVelocity(900, 0);
	projectile->loadResources();
	attachNode(std::move(projectile));
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

		setCollision(m_timeSinceDamage > DAMAGE_INVINCIBILITY_TIME);
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
	m_healthDisplay->setString(std::to_string(m_health) + " HP");
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
		return sf::Vector2f(0, -getMaxSpeed());
	case Direction::South:
		return sf::Vector2f(0, getMaxSpeed());
	case Direction::East:
		return sf::Vector2f( getMaxSpeed() + World::getScrollSpeed(), 0);
	case Direction::West:
		return sf::Vector2f(-(getMaxSpeed() - World::getScrollSpeed()), 0);
	default:
		return sf::Vector2f(0, 0);
	}
}

void Aircraft::loadResources()
{
	for (const auto& data : m_aircraftData)
	{
		if (data.type == getAircraftType())
		{
			m_health = data.health;
			m_speed = data.speed;
			m_aiRoutines = data.aiRoutines;
			m_despawnDistance = data.despawnDistance;
			m_enterDirection = data.enterDirection;
			m_exitDirection = data.exitDirection;
			setTextureId(data.textureId);
			setTextureLoadArea(data.textureLoadArea);
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
			vy = -1000;
			break;
		case Direction::East:
			vx = -2100;
			vy = 500;
			break;
		case Direction::West:
			vx = 0;
			vy = 500;
			break;
		case Direction::Count:
		default:
			vx = 0;
			vy = 0;
			break;
		}
		m_spawnPos = m_spawnPos + sf::Vector2f(vx, vy);
		setPosition(m_spawnPos);
	}

	m_fireCommand.nodeType = isAllied() ?  (unsigned int)NodeType::Player : (unsigned int)NodeType::Enemy;
	m_fireCommand.target = this;
	m_fireCommand.action =
		[this] (WorldNode& node, float dt)
		{
		  createBullets();
		};
	m_missileCommand.nodeType = isAllied() ?  (unsigned int)NodeType::Player : (unsigned int)NodeType::Enemy;
	m_missileCommand.target = this;
	m_missileCommand.action =
		[this] (WorldNode& node, float delta)
		{
		  createProjectile(Projectile::Missile, 0.f, 0.5f);
		};

	m_healthDisplay->setScale(getScale().x < 0 ? -1 : 1, 1);
}
