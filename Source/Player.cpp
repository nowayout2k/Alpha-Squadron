//
// Created by Johnnie Otis on 6/2/24.
//

#include <SFML/Window/Keyboard.hpp>
#include "../Header/Player.h"
#include "../Header/Enemy.h"
#include "../Header/AudioManager.h"
#include "../Header/Utility.h"
#include "../Header/Bullet.h"
#include "../Header/GameManager.h"

Player::Player() : SpriteEntity(true, "../Assets/Textures/AircraftSpriteSheet.png", sf::IntRect(240, 298, 52, 12))
{
    setScale(1.5f, 1.5f);
    sf::Vector2u windowSize = WindowManager::getSize();
    setPosition(0, windowSize.y / 2.f);
	m_timeSinceDamage = 0;
	m_isBeingDamaged = false;
	m_health = 100;
	m_fireCooldownRemaining = 0;
}

void Player::update(float deltaTime)
{
	Entity::update(deltaTime);
	if(m_fireCooldownRemaining > 0)
		m_fireCooldownRemaining -= deltaTime;
    sf::Vector2f offset = handleInput(deltaTime);
    move(offset);

	handleAnimation(deltaTime, offset);
}

sf::Vector2f Player::handleInput(float deltaTime)
{
    sf::Vector2f offset(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        offset.y -= 400.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        offset.y += 400.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        offset.x -= 400.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        offset.x += 400.f;

    if (offset.x != 0.f && offset.y != 0.f)
    {
        offset.x /= std::sqrt(2.f);
        offset.y /= std::sqrt(2.f);
    }

	offset *= deltaTime;

	adjustOffsetToWindow(offset);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		fireBullet(offset);

    return offset;
}

void Player::adjustOffsetToWindow(sf::Vector2f& offset)
{
    sf::Vector2u windowSize = WindowManager::getSize();
    sf::FloatRect windowBounds(0.f, 0.f, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));

    sf::FloatRect playerBounds = getGlobalBounds();
    playerBounds.left += offset.x;
    playerBounds.top += offset.y;

    if (playerBounds.left < windowBounds.left || playerBounds.left + playerBounds.width > windowBounds.width)
        offset.x = 0.f;
    if (playerBounds.top < windowBounds.top || playerBounds.top + playerBounds.height > windowBounds.height)
        offset.y = 0.f;
}

void Player::fireBullet(sf::Vector2f offset)
{
	if(m_fireCooldownRemaining > 0)
		return;

	auto spawnPos = getPosition() + offset + sf::Vector2f (m_texture.getSize().x, m_texture.getSize().y/2);
	GameManager::addEntity(std::move(std::make_unique<Bullet>(this, spawnPos, sf::Vector2f(500, 0))));
	m_fireCooldownRemaining = FIRE_COOLDOWN_TIME;
}

void Player::startDamageAnimation()
{
	m_timeSinceDamage = 0;
	m_isBeingDamaged = true;
}

void Player::handleAnimation(float deltaTime, sf::Vector2f offset)
{
	updateColor(deltaTime);
}

void Player::updateColor(float deltaTime)
{
	if(m_isBeingDamaged)
	{
		m_timeSinceDamage += deltaTime;
		Logger::Log(Verbose, "Damage Timer = " + std::to_string(m_timeSinceDamage));
		if(m_timeSinceDamage > DAMAGE_FLASH_TIME)
		{
			m_sprite->setColor(sf::Color::White);
			m_isBeingDamaged = false;
		}
		else
		{
			float phase = fmod(m_timeSinceDamage, 1.0f);
			float t = 0.5f * (1.0f + std::cos(phase * 2.0f * M_PI));
			float c = Utility::lerp(0, 255, t);
			m_sprite->setColor(sf::Color(255,c,c,255));
		}

		m_hasCollision = m_timeSinceDamage > DAMAGE_INVINCIBILITY_TIME;
	}
}

void Player::collision(const Entity* other)
{
	SpriteEntity::collision(other);
    const Enemy* enemy = dynamic_cast<const Enemy*>(other);
	const Bullet* bullet = dynamic_cast<const Bullet*>(other);
	if (bullet && bullet->hasCollision())
	{
		const Enemy* enemyOwner = dynamic_cast<const Enemy*>(bullet->getOwner());
		if(enemyOwner)
			takeDamage(20);
	}
    if (enemy && enemy->hasCollision())
	{
		takeDamage(10);
	}
}

void Player::takeDamage(int health)
{
	m_health -= health;
	if(m_isBeingDamaged || m_health <= 0)
	{
		destroy();
		return;
	}
	m_sprite->setColor(sf::Color::Red);
	AudioManager::playSound(SoundEffectType::Collect, 10);
	startDamageAnimation();
}

