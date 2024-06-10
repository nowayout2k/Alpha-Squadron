//
// Created by Johnnie Otis on 6/9/24.
//

#include "../Header/Character.h"
#include "../Header/Audio.h"
#include "../Header/Bullet.h"
#include "../Header/Scene.h"
#include "../Header/Utility.h"

#define DAMAGE_FLASH_TIME 4.0f
#define DAMAGE_INVINCIBILITY_TIME .3f
#define FIRE_COOLDOWN_TIME 0.2f

Character::Character(const bool hasCollision, const std::string& pathToTexture, const sf::IntRect textureRect) :
						SpriteEntity(hasCollision, pathToTexture, textureRect)
{
	m_timeSinceDamage = 0;
	m_isBeingDamaged = false;
	m_health = 100;
	m_fireCooldownRemaining = 0;
}

void Character::takeDamage(int health)
{
	m_health -= health;
	if(m_isBeingDamaged || m_health <= 0)
	{
		destroy();
		return;
	}
	setColor(sf::Color::Red);
	Audio::playSound(SoundEffectType::Collect, 10);
	m_timeSinceDamage = 0;
	m_isBeingDamaged = true;
}


void Character::fireBullet(sf::Vector2f offset, sf::Vector2f velocity)
{
	if(m_fireCooldownRemaining > 0)
		return;

	auto spawnPos = getPosition() + offset + sf::Vector2f(getScaledTextureSize().x, getScaledTextureSize().y/2);
	Scene::addEntity(std::move(std::make_unique<Bullet>(this, spawnPos, velocity)));
	m_fireCooldownRemaining = FIRE_COOLDOWN_TIME;
}

void Character::handleAnimation(float deltaTime, sf::Vector2f offset)
{
	if(m_isBeingDamaged)
	{
		m_timeSinceDamage += deltaTime;
		if(m_timeSinceDamage > DAMAGE_FLASH_TIME)
		{
			setColor(sf::Color::White);
			m_isBeingDamaged = false;
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
