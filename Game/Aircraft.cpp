//
// Created by Johnnie Otis on 6/9/24.
//

#include "Aircraft.h"
#include "../Engine/Audio.h"
#include "../Engine/Projectile.h"
#include "../Engine/World.h"
#include "../Engine/Engine.h"

#define DAMAGE_FLASH_TIME 4.0f
#define DAMAGE_INVINCIBILITY_TIME .3f
#define FIRE_COOLDOWN_TIME 0.2f
#ifndef M_PI
#define M_PI 3.14159265359
#endif

std::vector<AircraftData> Aircraft::m_aircraftData = LoadAircraftData("../Game/DataFiles/aircraftData.json");

Aircraft::Aircraft(const bool hasCollision, sf::Vector2f scale, sf::Vector2f position) : GameSprite(hasCollision)
{
	m_isMovingToStartPos = true;
	m_timeSinceDamage = 0;
	m_routineDistanceTravelled = 0;
	m_spawnDistanceTravelled = 0;
	m_routineIndex = 0;
	m_isDamageAnimationActive = false;
	m_fireCooldownRemaining = 0;
	m_spawnPos = position;
	setScale(scale);
	setPosition(m_spawnPos);
	std::unique_ptr<GameText> healthDisplay(new GameText(FontId::Gamer, "", 12, sf::Color::Black, sf::Text::Style::Regular, sf::Vector2f()));
	m_healthDisplay = healthDisplay.get();
	attachNode(std::move(healthDisplay));
}

void Aircraft::takeDamage(int health)
{
	m_health -= health;
	if(m_isDamageAnimationActive || m_health <= 0)
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


void Aircraft::handleAnimation(float deltaTime)
{
	handleDamageAnimation(deltaTime);
}

void Aircraft::fireBullet(sf::Vector2f velocity)
{
	if(m_fireCooldownRemaining > 0)
		return;

	auto offset = sf::Vector2f(0, getGlobalBounds().height/2);
	auto pro = std::make_unique<Projectile>((NodeType)getNodeType(), offset, velocity);
	m_fireCooldownRemaining = FIRE_COOLDOWN_TIME;
	pro->loadStateResources();
	attachNode(std::move(pro));
}

void Aircraft::handleDamageAnimation(float deltaTime)
{
	if(m_isDamageAnimationActive)
	{
		m_timeSinceDamage += deltaTime;
		if(m_timeSinceDamage > DAMAGE_FLASH_TIME)
		{
			setColor(sf::Color::White);
			m_isDamageAnimationActive = false;
		}
		else
		{
			float phase = fmod(m_timeSinceDamage, 1.0f);
			float t = 0.5 * (1.0f + std::cos(phase * 2.0f * M_PI));
			float c = Utility::lerp(0, 255, t);
			setColor(sf::Color(255,c,c,255));
		}
		setCollision(m_timeSinceDamage > DAMAGE_INVINCIBILITY_TIME);
	}
}

void Aircraft::update(float deltaTime)
{
	Entity::update(deltaTime);

	m_healthDisplay->setString(std::to_string(m_health) + " HP");
	auto bounds = GameSprite::getLocalBounds();
	m_healthDisplay->setPosition(bounds.width/2, -bounds.height/2);
	m_healthDisplay->setRotation(-getRotation());

	if(m_fireCooldownRemaining > 0)
		m_fireCooldownRemaining -= deltaTime;

	if(!(getNodeType() & static_cast<unsigned int>(NodeType::Player)))
	{
		auto pos = getPosition();
		Debug::log("CURRENT pos x:" + std::to_string(pos.x) + " y:" + std::to_string(pos.y));

		auto& view = Engine::getWindow().getView();
		sf::Vector2f center = view.getCenter();
		sf::Vector2f size = view.getSize();

		auto viewRect = sf::FloatRect(center - size / 2.f, size);

		if(viewRect.left + viewRect.width > m_spawnPos.x + m_despawnDistance)
			m_isExiting = true;

		if(m_spawnDistanceTravelled > 500)
			m_isMovingToStartPos = false;

		if(m_isMovingToStartPos)
		{
			Debug::log("ai Enter called");
			float vx = 0;
			float vy = 0;
			switch (m_enterDirection)
			{
			case Direction::North:
				vx = 0;
				vy = -getMaxSpeed();
				break;
			case Direction::South:
				vx = 0;
				vy = getMaxSpeed();
				break;
			case Direction::East:
				vx = World::getScrollSpeed() + getMaxSpeed();
				vy = 0;
				break;
			case Direction::West:
				vx = World::getScrollSpeed() - getMaxSpeed();
				vy = 0;
				break;
			}
			setVelocity(sf::Vector2f(vx, vy));
			m_spawnDistanceTravelled += getMaxSpeed() * deltaTime;
		}
		else if(m_isExiting)
		{
			Debug::log("ai Exit called");
			float vx = 0;
			float vy = 0;
			switch (m_exitDirection)
			{
			case Direction::North:
				vx = 0;
				vy = -getMaxSpeed();
				break;
			case Direction::South:
				vx = 0;
				vy = getMaxSpeed();
				break;
			case Direction::East:
				vx = World::getScrollSpeed() + getMaxSpeed();
				vy = 0;
				break;
			case Direction::West:
				vx = World::getScrollSpeed() - getMaxSpeed();
				vy = 0;
				break;
			}
			setVelocity(sf::Vector2f(vx, vy));
		}
		else if(m_aiRoutines.size() > 0)
		{
			float distanceToTravel = m_aiRoutines[m_routineIndex].distance;
			if (m_routineDistanceTravelled > distanceToTravel)
			{
				m_routineIndex = (m_routineIndex + 1) % m_aiRoutines.size();
				m_routineDistanceTravelled = 0.f;
			}
			float radians = Utility::toRadian(m_aiRoutines[m_routineIndex].angle);
			float vx = World::getScrollSpeed() + getMaxSpeed() * std::cos(radians);
			float vy = getMaxSpeed() * std::sin(radians);
			Debug::log("Set Ai Velocity to x: " + std::to_string(vx) + " Y:" +std::to_string(vy) + " sin:" +  std::to_string(std::sin(radians)) + " cos:" + std::to_string(std::cos(radians)));
			setVelocity(sf::Vector2f(vx, vy));
			m_routineDistanceTravelled += getMaxSpeed() * deltaTime;
		}
	}
}

void Aircraft::loadResources()
{
	Debug::log("Aircraft Type: " + Utility::aircraftTypeToString(getAircraftType()));
	for (auto& data: m_aircraftData)
	{
		Debug::log("Data Aircraft Type: " + Utility::aircraftTypeToString(data.type));
		if(data.type == getAircraftType())
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

	if(!(getNodeType() & static_cast<unsigned int>(NodeType::Player)))
	{
		float vx = 0;
		float vy = 0;
		switch (m_enterDirection)
		{
		case Direction::North:
			vx = -100;
			vy = 1000;
			break;
		case Direction::South:
			vx = -1000;
			vy = 500;
			break;
		case Direction::East:
			vx = -1500;
			vy = 500;
			break;
		case Direction::West:
			vx = 0;
			vy = 500;
			break;
		}
		m_spawnPos = m_spawnPos + sf::Vector2f(vx, vy);
		setPosition(m_spawnPos);
	}

	m_healthDisplay->setScale(getScale().x < 0 ? -1 : 1, 1);
}
