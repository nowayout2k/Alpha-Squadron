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
	auto windowSize = WindowManager::getSize();
    m_entities.push_back(std::make_unique<ScrollingBackground>());
    m_entities.push_back(std::make_unique<Player>(true));
    m_entities.push_back(std::make_unique<Enemy>(true, sf::Vector2f(windowSize.x-200, windowSize.y/2)));
	m_entities.push_back(std::make_unique<Enemy>(true, sf::Vector2f(windowSize.x-100, windowSize.y/2)));
	AudioManager::playMusic(MusicType::Level1, 10);
}

void GameManager::update(float deltaTime)
{
	for (auto it = m_entities.begin(); it != m_entities.end(); )
	{
		if (!(*it)->isAlive())
		{
			it = m_entities.erase(it);
		}
		else
		{
			(*it)->update(deltaTime);
			++it;
		}
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

