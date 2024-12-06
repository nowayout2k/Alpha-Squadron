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
	static float getScrollSpeed() { return m_scrollSpeed; }

private:
	struct SpawnPoint
	{
		SpawnPoint(AircraftType type, float x, float y) : type(type), x(x), y(y){}
		AircraftType type;
		float x;
		float y;
	};

	friend class Debug;

	void setup();
	void loadResources();
	sf::FloatRect getBattlefieldBounds() { return ; }
	static void handleCollisions();
	static float m_scrollSpeed;

	sf::RenderWindow& m_window;
	sf::View m_worldView;
	EmptyWorldNode m_worldGraph;
	std::array<WorldNode*, static_cast<int>(Layer::LayerCount)> m_worldLayers;
	sf::FloatRect m_worldBounds;
	std::vector<SpawnPoint> m_enemySpawnPoints;
	sf::Vector2f m_spawnPosition;
	sf::Vector2f m_viewPositionOffset;
	Aircraft* m_playerAircraft;
	CommandQueue m_commandQueue;
};


#endif //WORLD_H_
