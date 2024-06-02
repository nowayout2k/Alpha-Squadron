//
// Created by Johnnie Otis on 6/2/24.
//

#include <SFML/Window/Keyboard.hpp>
#include "../Header/Player.h"
#include "../Header/Enemy.h"

Player::Player(const std::string& pathToTexture, const bool hasCollision) : SpriteEntity(pathToTexture, hasCollision)
{
    setScale(0.1f, 0.1f);
    sf::Vector2u windowSize = WindowManager::GetSize();
    setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
}

void Player::Update(float deltaTime)
{
    sf::Vector2f offset = HandleInput();
    AdjustOffsetToWindow(offset);
    move(offset);
}

sf::Vector2f Player::HandleInput()
{
    sf::Vector2f offset(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        offset.y -= 10.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        offset.y += 10.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        offset.x -= 10.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        offset.x += 10.f;

    if (offset.x != 0.f && offset.y != 0.f)
    {
        offset.x /= std::sqrt(2.f);
        offset.y /= std::sqrt(2.f);
    }

    return offset;
}

void Player::AdjustOffsetToWindow(sf::Vector2f& offset)
{
    sf::Vector2u windowSize = WindowManager::GetSize();
    sf::FloatRect windowBounds(0.f, 0.f, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));

    sf::FloatRect playerBounds = GetGlobalBounds();
    playerBounds.left += offset.x;
    playerBounds.top += offset.y;

    if (playerBounds.left < windowBounds.left || playerBounds.left + playerBounds.width > windowBounds.width)
        offset.x = 0.f;
    if (playerBounds.top < windowBounds.top || playerBounds.top + playerBounds.height > windowBounds.height)
        offset.y = 0.f;
}

void Player::Collision(const Entity* other)
{
    SpriteEntity::Collision(other);
    const Enemy* enemy = dynamic_cast<const Enemy*>(other);
    if (enemy)
        m_sprite->setColor(sf::Color::Red);
}
