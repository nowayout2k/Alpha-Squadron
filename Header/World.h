//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef WORLD_H_
#define WORLD_H_

#include "GameSprite.h"
#include "Entity.h"

class World
{
public:
	World() {};

	template<typename T, typename = std::enable_if_t<std::is_base_of<Entity, T>::value>>
	static void addEntity(std::unique_ptr<T>&& entity) { m_pendingEntities.push_back(std::move(entity)); }
	void restart();
	void update(float deltaTime);
	void render(sf::RenderWindow& window, sf::RenderStates states);
	void setup();
	void loadResources();
private:
	static void handleCollisions();
	static std::vector<std::unique_ptr<Entity>> m_entities;
	static std::vector<std::unique_ptr<Entity>> m_pendingEntities;
};


#endif //WORLD_H_
