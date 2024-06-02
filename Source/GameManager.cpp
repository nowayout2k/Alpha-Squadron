//
// Created by Johnnie Otis on 5/30/24.
//

#include "../Header/GameManager.h"
#include "../Header/Input.h"

GameManager::GameManager()
{
    SetUpInput();
    std::unique_ptr<sf::Drawable> entity;
    entity = std::make_unique<Player>();
}
void GameManager::WPressed(std::vector<Input::InputEventInfo> otherKeys)
{
    sf::Vector2f offset(0, -10);
    for (Input::InputEventInfo info : otherKeys)
    {
        if(info.InputValue == sf::Keyboard::Key::Up)
        {
            offset = sf::Vector2f(0, 0);
            break;
        }
        if(info.InputValue == sf::Keyboard::Key::Left || info.InputValue == sf::Keyboard::Key::Right ||
           info.InputValue == sf::Keyboard::Key::A || info.InputValue == sf::Keyboard::Key::D)
        {
            offset = sf::Vector2f(0, -5);
        }

    }

    player.MovePosition(offset);
}

void GameManager::SPressed(std::vector<Input::InputEventInfo> otherKeys)
{
    sf::Vector2f offset(0, 10);
    for (Input::InputEventInfo info : otherKeys)
    {
        if(info.InputValue == sf::Keyboard::Key::Down)
        {
            offset = sf::Vector2f(0, 0);
            break;
        }
        if(info.InputValue == sf::Keyboard::Key::Left || info.InputValue == sf::Keyboard::Key::Right ||
           info.InputValue == sf::Keyboard::Key::A || info.InputValue == sf::Keyboard::Key::D)
        {
            offset = sf::Vector2f(0, 5);
        }

    }

    player.MovePosition(offset);
};
void GameManager::APressed(std::vector<Input::InputEventInfo> otherKeys)
{
    sf::Vector2f offset(-10, 0);
    for (Input::InputEventInfo info : otherKeys)
    {
        if(info.InputValue == sf::Keyboard::Key::Left)
        {
            offset = sf::Vector2f(0, 0);
            break;
        }
        if(info.InputValue == sf::Keyboard::Key::Up || info.InputValue == sf::Keyboard::Key::Down ||
           info.InputValue == sf::Keyboard::Key::W || info.InputValue == sf::Keyboard::Key::S)
        {
            offset = sf::Vector2f(-5, 0);
        }

    }

    player.MovePosition(offset);
}
void GameManager::DPressed(std::vector<Input::InputEventInfo> otherKeys)
{
    sf::Vector2f offset(10, 0);
    for (Input::InputEventInfo info : otherKeys)
    {
        if(info.InputValue == sf::Keyboard::Key::Right)
        {
            offset = sf::Vector2f(0, 0);
            break;
        }
        if(info.InputValue == sf::Keyboard::Key::Up || info.InputValue == sf::Keyboard::Key::Down ||
           info.InputValue == sf::Keyboard::Key::W || info.InputValue == sf::Keyboard::Key::S)
        {
            offset = sf::Vector2f(5, 0);
        }

    }

    player.MovePosition(offset);
}
void GameManager::UpPressed(std::vector<Input::InputEventInfo> otherKeys)
{
    sf::Vector2f offset(0, -10);
    for (Input::InputEventInfo info : otherKeys)
    {
        if(info.InputValue == sf::Keyboard::Key::Left || info.InputValue == sf::Keyboard::Key::Right ||
           info.InputValue == sf::Keyboard::Key::A || info.InputValue == sf::Keyboard::Key::D)
        {
            offset = sf::Vector2f(0, -5);
        }

    }

    player.MovePosition(offset);
}
void GameManager::DownPressed(std::vector<Input::InputEventInfo> otherKeys)
{
    sf::Vector2f offset(0, 10);
    for (Input::InputEventInfo info : otherKeys)
    {
        if(info.InputValue == sf::Keyboard::Key::Left || info.InputValue == sf::Keyboard::Key::Right ||
           info.InputValue == sf::Keyboard::Key::A || info.InputValue == sf::Keyboard::Key::D)
        {
            offset = sf::Vector2f(0, 5);
        }

    }

    player.MovePosition(offset);
}
void GameManager::LeftPressed(std::vector<Input::InputEventInfo> otherKeys)
{
    sf::Vector2f offset(-10, 0);
    for (Input::InputEventInfo info : otherKeys)
    {
        if(info.InputValue == sf::Keyboard::Key::Up || info.InputValue == sf::Keyboard::Key::Down ||
           info.InputValue == sf::Keyboard::Key::W || info.InputValue == sf::Keyboard::Key::S)
        {
            offset = sf::Vector2f(-5, 0);
        }

    }

    player.MovePosition(offset);
}
void GameManager::RightPressed(std::vector<Input::InputEventInfo> otherKeys)
{
    sf::Vector2f offset(10, 0);
    for (Input::InputEventInfo info : otherKeys)
    {
        if(info.InputValue == sf::Keyboard::Key::Up || info.InputValue == sf::Keyboard::Key::Down ||
           info.InputValue == sf::Keyboard::Key::W || info.InputValue == sf::Keyboard::Key::S)
        {
            offset = sf::Vector2f(5, 0);
        }
    }

    player.MovePosition(offset);
}

void GameManager::SetUpInput()
{
    Input::SubscribeKey(sf::Keyboard::Key::W, std::bind(&GameManager::WPressed, this, std::placeholders::_1));
    Input::SubscribeKey(sf::Keyboard::Key::S,std::bind(&GameManager::SPressed, this, std::placeholders::_1));
    Input::SubscribeKey(sf::Keyboard::Key::A,std::bind(&GameManager::APressed, this, std::placeholders::_1));
    Input::SubscribeKey(sf::Keyboard::Key::D, std::bind(&GameManager::DPressed, this, std::placeholders::_1));

    Input::SubscribeKey(sf::Keyboard::Key::Up,std::bind(&GameManager::UpPressed, this, std::placeholders::_1));
    Input::SubscribeKey(sf::Keyboard::Key::Down,std::bind(&GameManager::DownPressed, this, std::placeholders::_1));
    Input::SubscribeKey(sf::Keyboard::Key::Left,std::bind(&GameManager::LeftPressed, this, std::placeholders::_1));
    Input::SubscribeKey(sf::Keyboard::Key::Right,std::bind(&GameManager::RightPressed, this, std::placeholders::_1));
}
