//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef WORLD_H_
#define WORLD_H_

#include <array>
#include <queue>
#include "GameSprite.h"
#include "Entity.h"
#include "../Game/Aircraft.h"
#include "Layer.h"
#include "EmptyWorldNode.h"
#include "CommandQueue.h"

class World
{
public:
	explicit World(sf::RenderWindow& window);
	void restart();
	void update(float deltaTime);
	void render(sf::RenderWindow &window, sf::RenderStates states);
	CommandQueue& getCommandQueue() { return m_commandQueue; }
private:
	friend class Debug;

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
	sf::Vector2f m_viewPositionOffset;
	Aircraft* m_playerAircraft;
	CommandQueue m_commandQueue;
};


#endif //WORLD_H_
