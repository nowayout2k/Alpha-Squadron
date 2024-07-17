//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef WORLD_H_
#define WORLD_H_

#include <array>
#include "GameSprite.h"
#include "Entity.h"
#include "Aircraft.h"
#include "Layer.h"
#include "EmptyWorldNode.h"

class World
{
public:
	explicit World(sf::RenderWindow& window);
	void restart();
	void update(float deltaTime);
	void render(sf::RenderWindow &window, sf::RenderStates states);
private:
	void setup();
	void loadResources();
	static void handleCollisions();

	sf::RenderWindow& m_window;
	sf::View m_worldView;
	EmptyWorldNode m_worldGraph;
	std::array<WorldNode*, Layer::LayerCount> m_worldLayers;
	sf::FloatRect m_worldBounds;
	sf::Vector2f m_spawnPosition;
	float m_scrollSpeed;
	float m_totalMovement;
	Aircraft* m_playerAircraft;
};


#endif //WORLD_H_
