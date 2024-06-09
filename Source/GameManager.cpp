//
// Created by Johnnie Otis on 5/30/24.
//

#include <SFML/Window/Keyboard.hpp>
#include "../Header/GameManager.h"
#include "../Header/Enemy.h"
#include "../Header/Player.h"
#include "../Header/ScrollingBackground.h"
#include "../Header/AudioManager.h"

std::vector<std::unique_ptr<Entity>> GameManager::m_entities;
std::vector<std::unique_ptr<Entity>> GameManager::m_pendingEntities;

GameManager::GameManager()
{
	auto windowSize = WindowManager::getSize();
	m_entities.push_back(std::make_unique<ScrollingBackground>(std::vector<std::string>{"../Assets/Textures/Background.jpg", "../Assets/Textures/Background.jpg"}));
    m_entities.push_back(std::make_unique<Player>());
    m_entities.push_back(std::make_unique<Enemy>(true, sf::Vector2f(windowSize.x-200, windowSize.y/2)));
	m_entities.push_back(std::make_unique<Enemy>(true, sf::Vector2f(windowSize.x-100, windowSize.y/2)));
	AudioManager::playMusic(MusicType::Level1, 10);
}

void GameManager::update(float deltaTime)
{
	for (auto& entity : m_pendingEntities)
	{
		m_entities.push_back(std::move(entity));
	}
	m_pendingEntities.clear();

	for (auto it = m_entities.begin(); it != m_entities.end(); )
	{
		if ((*it)->isDestroyPending())
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
		auto drawableEntity = dynamic_cast<sf::Drawable*>(entity.get());
		if(drawableEntity)
			window.draw(*drawableEntity);
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
            if(spriteEntity && spriteEntityOther && spriteEntity->isColliding(spriteEntityOther->getGlobalBounds()))
            {
				spriteEntity->collision(other.get());
            }
        }
    }
}

