//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef ALPHA_SQUADRON_GAMEMANAGER_H
#define ALPHA_SQUADRON_GAMEMANAGER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "SpriteEntity.h"
#include "Entity.h"

static class GameManager
{
public:
	template<typename T, typename = std::enable_if_t<std::is_base_of<Entity, T>::value>>
	static void addEntity(std::unique_ptr<T>&& entity)
	{
		m_pendingEntities.push_back(std::move(entity));
	}

	void update(float deltaTime);
	void render(sf::RenderWindow& window);
	GameManager();
private:
	static void handleCollisions();
	static std::vector<std::unique_ptr<Entity>> m_entities;
	static std::vector<std::unique_ptr<Entity>> m_pendingEntities;
};


#endif //ALPHA_SQUADRON_GAMEMANAGER_H
