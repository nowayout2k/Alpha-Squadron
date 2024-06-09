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
	levelSetup();
}

void GameManager::restart()
{
	levelSetup();
}

void GameManager::levelSetup()
{
	m_entities.clear();
	m_pendingEntities.clear();
	auto windowSize = WindowManager::getSize();
	addEntity(std::make_unique<SpriteEntity>(false, "../Assets/Textures/sky.png"));
	addEntity(std::make_unique<ScrollingBackground>(std::vector<std::string>{"../Assets/Textures/house1.png", "../Assets/Textures/house1.png", "../Assets/Textures/house1.png"}));
	addEntity(std::make_unique<Player>());
	addEntity(std::make_unique<Enemy>(true, sf::Vector2f((float)windowSize.x-500, (float)windowSize.y+100)));
	addEntity(std::make_unique<Enemy>(true, sf::Vector2f((float)windowSize.x-100, (float)windowSize.y+100)));
	AudioManager::playMusic(MusicType::Level1, 10);
}

void GameManager::update(float deltaTime)
{
	for (auto& entity : m_pendingEntities)
	{
		m_entities.push_back(std::move(entity));
	}
	m_pendingEntities.clear();

	bool hasEnemy = false;
	bool hasPlayer = false;
	for (auto it = m_entities.begin(); it != m_entities.end();)
	{
		auto enemy = dynamic_cast<Enemy*>(it->get());
		if (enemy)
			hasEnemy = true;

		auto player = dynamic_cast<Player*>(it->get());
		if(player)
			hasPlayer = true;

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

	if(!hasPlayer)
	{
		restart();
		return;
	}
	if (!hasEnemy)
	{
		auto windowSize = WindowManager::getSize();
		addEntity(std::make_unique<Enemy>(true, sf::Vector2f((float)windowSize.x-500, (float)windowSize.y+100)));
		addEntity(std::make_unique<Enemy>(true, sf::Vector2f((float)windowSize.x-100, (float)windowSize.y+100)));
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
		if(entity->isDestroyPending())
			continue;

        for (const auto& other : m_entities)
        {
            if(other->isDestroyPending() && entity == other)
                continue;

            auto spriteEntity = dynamic_cast<SpriteEntity*>(entity.get());
            auto spriteEntityOther = dynamic_cast<SpriteEntity*>(other.get());
            if(spriteEntity && spriteEntity->hasCollision() && spriteEntityOther && spriteEntityOther->hasCollision() &&
				spriteEntity->isColliding(spriteEntityOther->getGlobalBounds()))
            {
				spriteEntity->collision(other.get());
            }
        }
    }
}

