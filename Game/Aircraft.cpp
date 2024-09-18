//
// Created by Johnnie Otis on 6/9/24.
//

#include "Aircraft.h"
#include "../Engine/Audio.h"
#include "../Engine/Projectile.h"
#include "../Engine/World.h"
#include "../Engine/Utility.h"

#define DAMAGE_FLASH_TIME 4.0f
#define DAMAGE_INVINCIBILITY_TIME .3f
#define FIRE_COOLDOWN_TIME 0.2f
#ifndef M_PI
	#define M_PI 3.14159265359
#endif

Aircraft::Aircraft(const bool hasCollision, const TextureId textureType, const sf::IntRect textureRect) :
	GameSprite(hasCollision, textureType, textureRect)
{
	m_timeSinceDamage = 0;
	m_isDamageAnimationActive = false;
	m_health = 100;
	m_fireCooldownRemaining = 0;
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


WorldNode::SmartNode Aircraft::fireBullet(sf::Vector2f velocity)
{
	if(m_fireCooldownRemaining > 0)
		return nullptr;

	auto offset = sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height/2);
	float sign = velocity.x < 0 ? -1 : 1;
	auto worldPos = getWorldPosition();
	auto pro = std::make_unique<Projectile>((NodeType)getNodeType(), worldPos + offset * sign, velocity);
	m_fireCooldownRemaining = FIRE_COOLDOWN_TIME;
	return std::move(pro);
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
	if(m_fireCooldownRemaining > 0)
		m_fireCooldownRemaining -= deltaTime;
}
