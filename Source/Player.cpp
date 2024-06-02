//
// Created by Johnnie Otis on 5/30/24.
//

#include <SFML/Window/Keyboard.hpp>
#include "../Header/Player.h"
#include "../Header/Enemy.h"
#include "../Header/WindowManager.h"

Player::Player()
{
    m_texture.loadFromFile("../Assets/Textures/Player.png");
    SetTexture(m_texture);
    SetScale(sf::Vector2f(.1,.1));
}

void Player::Update()
{
    sf::Vector2f offset(0, 0);

    bool moveUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    bool moveDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    bool moveLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    bool moveRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);

    if (moveUp) offset.y -= 10;
    if (moveDown) offset.y += 10;
    if (moveLeft) offset.x -= 10;
    if (moveRight) offset.x += 10;

    if ((moveUp || moveDown) && (moveLeft || moveRight))
    {
        offset.x /= std::sqrt(2);
        offset.y /= std::sqrt(2);
    }

    /*sf::Vector2u windowSize = WindowManager::GetSize();
    sf::FloatRect windowBounds(0, 0, static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));

    auto playerBounds = GetGlobalBounds();
    if(windowBounds.intersects(playerBounds))
    {
        if(windowBounds.left > playerBounds.left)
            offset.x = playerBounds.left + windowBounds.left;
        if(windowBounds.left + windowBounds.width < playerBounds.left + playerBounds.width)
            offset.x = (playerBounds.left + playerBounds.width) - (windowBounds.left + windowBounds.width);
        if(windowBounds.top < playerBounds.top)
            offset.y = playerBounds.top + windowBounds.top;
        if(windowBounds.top + windowBounds.height > playerBounds.top + playerBounds.height)
            offset.y = (playerBounds.top + playerBounds.height) + (windowBounds.top + windowBounds.height);
    }*/

    MovePosition(offset);
}

void Player::Collision(const Entity* other)
{
    const Enemy* enemy = dynamic_cast<const Enemy*>(other);
    if (enemy)
        m_sprite.setColor(sf::Color::Red);
}
