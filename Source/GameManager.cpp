//
// Created by Johnnie Otis on 5/30/24.
//

#include <SFML/Window/Keyboard.hpp>
#include "../Header/GameManager.h"
#include "../Header/Enemy.h"
#include "../Header/Player.h"
#include "../Header/ScrollingBackground.h"
#include "../Header/AudioManager.h"

GameManager::GameManager()
{
    m_entities.push_back(std::make_unique<ScrollingBackground>());
    m_entities.push_back(std::make_unique<Player>(true));
    m_entities.push_back(std::make_unique<Enemy>(true));
	AudioManager::playMusic(MusicType::Level1, 10);
}

void GameManager::update(float deltaTime)
{
    for (const auto& entity : m_entities)
    {
		entity->update(deltaTime);
    }
	handleCollisions();
}

void GameManager::render(sf::RenderWindow &window)
{
    for (const auto& entity : m_entities)
    {
        window.draw(*entity);
    }
}

void GameManager::handleCollisions()
{
    for (const auto& entity : m_entities)
    {
        for (const auto& other : m_entities)
        {
            if(entity == other)
                continue;

            auto spriteEntity = dynamic_cast<SpriteEntity*>(entity.get());
            auto spriteEntityOther = dynamic_cast<SpriteEntity*>(other.get());
            if(spriteEntity && spriteEntity->isColliding(spriteEntityOther->getGlobalBounds()))
            {
				entity->collision(other.get());
            }
        }
    }
}

