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
	void render(sf::RenderWindow &window, sf::RenderStates states);
	CommandQueue& getCommandQueue() { return m_commandQueue; }
	static float getScrollSpeed() { return m_scrollSpeed; }
	sf::FloatRect getViewBounds() const;
	sf::FloatRect getBattlefieldBounds() const;
	void update(float deltaTime);
private:
	struct SpawnPoint
	{
		SpawnPoint(AircraftType type, float spawnDistance) : type(type), spawnDistance(spawnDistance){}
		AircraftType type;
		float spawnDistance;
	};

	friend class Debug;

	void setup();
	void loadResources();
	static void handleCollisions();
	std::unique_ptr<Aircraft> createAircraft(AircraftType type, sf::Vector2f position, NodeType nodeType, sf::Vector2f scale);
	void spawnEnemies();
	sf::Vector2f getSpawnLocationOffset(int spawnLocation);
	void addEnemies();
	void guideMissiles();
	static float m_scrollSpeed;

	sf::RenderWindow& m_window;
	sf::View m_worldView;
	EmptyWorldNode m_worldGraph;
	std::array<WorldNode*, static_cast<int>(Layer::LayerCount)> m_worldLayers;
	sf::FloatRect m_worldBounds;
	std::vector<SpawnPoint> m_enemySpawnPoints;
	std::vector<Aircraft*> m_activeEnemies;
	sf::Vector2f m_spawnPosition;
	sf::Vector2f m_viewPositionOffset;
	Aircraft* m_playerAircraft;
	CommandQueue m_commandQueue;
};


#endif //WORLD_H_
