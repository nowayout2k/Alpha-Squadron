//
// Created by Johnnie Otis on 6/9/24.
//

#include "../Header/Aircraft.h"
#include "../Header/Audio.h"
#include "../Header/Projectile.h"
#include "../Header/World.h"
#include "../Header/Utility.h"

#define DAMAGE_FLASH_TIME 4.0f
#define DAMAGE_INVINCIBILITY_TIME .3f
#define FIRE_COOLDOWN_TIME 0.2f

Aircraft::Aircraft(EntityType entityType, const bool hasCollision, const TextureId textureType, const sf::IntRect textureRect) :
	GameSprite(entityType, hasCollision, textureType, textureRect)
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


void Aircraft::fireBullet(sf::Vector2f pos, sf::Vector2f velocity)
{
	if(m_fireCooldownRemaining > 0)
		return;

	auto offset = sf::Vector2f(getScaledTextureSize().x, getScaledTextureSize().y/2);
	auto spawnPos = velocity.x < 0 ? pos - offset: pos +  offset;
	//World::addEntity(std::move(std::make_unique<Projectile>(getEntityType(), spawnPos, velocity)));
	m_fireCooldownRemaining = FIRE_COOLDOWN_TIME;
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
