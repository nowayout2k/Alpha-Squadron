//
// Created by Johnnie Otis on 6/9/24.
//

#include "Aircraft.h"
#include "../Engine/Audio.h"
#include "../Engine/Projectile.h"
#include "../Engine/World.h"

#define DAMAGE_FLASH_TIME 4.0f
#define DAMAGE_INVINCIBILITY_TIME .3f
#define FIRE_COOLDOWN_TIME 0.2f
#ifndef M_PI
	#define M_PI 3.14159265359
#endif

std::vector<AircraftData> Aircraft::m_aircraftData = LoadAircraftData("../Game/DataFiles/aircraftData.json");

Aircraft::Aircraft(const bool hasCollision, sf::Vector2f scale) : Aircraft(hasCollision)
{
	setScale(scale);
}

Aircraft::Aircraft(const bool hasCollision) : GameSprite(hasCollision)
{
	m_timeSinceDamage = 0;
	m_travelledDistance = 0;
	m_directionIndex = 0;
	m_isDamageAnimationActive = false;
	m_fireCooldownRemaining = 0;
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

void Aircraft::handleAnimation(float deltaTime)
{
	handleDamageAnimation(deltaTime);
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
	m_healthDisplay->setPosition(25.f, -5.f);
	m_healthDisplay->setRotation(-getRotation());


	if(m_fireCooldownRemaining > 0)
		m_fireCooldownRemaining -= deltaTime;

	if(!(getNodeType() & static_cast<unsigned int>(NodeType::Player)) && m_directions.size() > 0)
	{
		float distanceToTravel = m_directions[m_directionIndex].distance;
		if (m_travelledDistance > distanceToTravel)
		{
			Debug::log("Direction Index: " + std::to_string(m_directionIndex));
			m_directionIndex = (m_directionIndex + 1) % m_directions.size();
			m_travelledDistance = 0.f;
		}
		float radians = Utility::toRadian(m_directions[m_directionIndex].angle);
		float vx = World::getScrollSpeed() + getMaxSpeed() * std::cos(radians);
		float vy = getMaxSpeed() * std::sin(radians);
		setVelocity(vx, vy);
		m_travelledDistance += getMaxSpeed() * deltaTime;
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
			m_directions = data.directions;
			setTextureId(data.textureId);
			setTextureLoadArea(data.textureLoadArea);
			Debug::log("Found Aircraft");
		}
	}
	GameSprite::loadResources();

	Debug::log("scale " + std::to_string( getScale().x));
	m_healthDisplay->setScale(getScale().x < 0 ? -1 : 1, 1);
}
