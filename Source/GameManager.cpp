//
// Created by Johnnie Otis on 5/30/24.
//

#include <SFML/Window/Keyboard.hpp>
#include "../Header/GameManager.h"
#include "../Header/Enemy.h"

GameManager::GameManager()
{
    entities.push_back(std::make_unique<Player>());
    entities.push_back(std::make_unique<Enemy>());
}

void GameManager::Update()
{
    for (const auto& entity : entities)
    {
        entity->Update();
    }
    HandleCollisions();
}

void GameManager::Render(sf::RenderWindow &window)
{
    for (const auto& entity : entities)
    {
        window.draw(*entity);
    }
}

void GameManager::HandleCollisions()
{
    for (const auto& entity : entities)
    {
        for (const auto& other : entities)
        {
            if(entity == other)
                continue;

            if(entity->IsColliding(other->GetGlobalBounds()))
            {
                entity->Collision(other.get());
            }
        }
    }
}

