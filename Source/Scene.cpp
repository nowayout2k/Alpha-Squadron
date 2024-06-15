//
// Created by Johnnie Otis on 5/30/24.
//

#include "../Header/Scene.h"
#include "../Header/Enemy.h"
#include "../Header/Player.h"
#include "../Header/ScrollingBackground.h"
#include "../Header/Audio.h"
#include "../Header/GameText.h"
#include "../Header/Game.h"

std::vector<std::unique_ptr<Entity>> Scene::m_entities;
std::vector<std::unique_ptr<Entity>> Scene::m_pendingEntities;

void Scene::restart()
{
	setup();
}

void Scene::setup()
{
	m_entities.clear();
	m_pendingEntities.clear();
	auto windowSize = Game::getWindowSize();
	m_entities.push_back(std::make_unique<GameSprite>(false, TextureType::SmoggySky));
	m_entities.push_back(std::make_unique<ScrollingBackground>(std::vector<TextureType>{TextureType::DecayedBuildings1, TextureType::DecayedBuildings1, TextureType::DecayedBuildings1}));
	m_entities.push_back(std::make_unique<Player>());
	m_entities.push_back(std::make_unique<Enemy>(true, sf::Vector2f((float)windowSize.x-500, (float)windowSize.y+100)));
	m_entities.push_back(std::make_unique<Enemy>(true, sf::Vector2f((float)windowSize.x-100, (float)windowSize.y+100)));
	Audio::playMusic(MusicType::UNSquadronLevel1, 10);

	loadResources();
}

void Scene::loadResources()
{
	for (auto& entity : m_entities)
	{
		entity->loadResources();
	}
}

void Scene::update(float deltaTime)
{
	for (auto& entity : m_pendingEntities)
	{
		entity->loadResources();
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
		auto windowSize = Game::getWindowSize();
		addEntity(std::make_unique<Enemy>(true, sf::Vector2f((float)windowSize.x-500, (float)windowSize.y+100)));
		addEntity(std::make_unique<Enemy>(true, sf::Vector2f((float)windowSize.x-100, (float)windowSize.y+100)));
	}

	handleCollisions();
}

void Scene::render(sf::RenderWindow &window, sf::RenderStates states)
{
    for (const auto& entity : m_entities)
    {
		entity->render(window, states);
    }
}

void Scene::handleCollisions()
{
    for (const auto& entity : m_entities)
    {
		if(entity->isDestroyPending())
			continue;

        for (const auto& other : m_entities)
        {
            if(other->isDestroyPending() && entity == other)
                continue;

            if(entity && entity->hasCollision() && other && other->hasCollision() &&
				entity->isColliding(other->getGlobalBounds()))
            {
				entity->collision(other.get());
            }
        }
    }
}

