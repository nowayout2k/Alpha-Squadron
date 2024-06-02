//
// Created by Johnnie Otis on 5/30/24.
//

#include <SFML/Window/Keyboard.hpp>
#include "../Header/GameManager.h"
#include "../Header/Enemy.h"
#include "../Header/Player.h"
#include "../Header/ScrollingBackground.h"

GameManager::GameManager()
{
    entities.push_back(std::make_unique<ScrollingBackground>("../Assets/Textures/Background.jpg"));
    entities.push_back(std::make_unique<Player>("../Assets/Textures/Player.png", true));
    entities.push_back(std::make_unique<Enemy>("../Assets/Textures/Player.png", true));
}

void GameManager::Update(float deltaTime)
{
    for (const auto& entity : entities)
    {
        entity->Update(deltaTime);
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

            auto spriteEntity = dynamic_cast<SpriteEntity*>(entity.get());
            auto spriteEntityOther = dynamic_cast<SpriteEntity*>(other.get());
            if(spriteEntity && spriteEntity->IsColliding(spriteEntityOther->GetGlobalBounds()))
            {
                entity->Collision(other.get());
            }
        }
    }
}

