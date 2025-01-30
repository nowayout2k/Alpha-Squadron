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
	static GameData GameData;
private:
	struct EnemySpawnPoint
	{
		EnemySpawnPoint(AircraftType type, float spawnDistance) : Type(type), SpawnDistance(spawnDistance){}
		AircraftType Type;
		float SpawnDistance;
	};

	struct PickupSpawnPoint
	{
		PickupSpawnPoint(PickupType type, float spawnDistance, sf::Vector2f offset) : Type(type), SpawnDistance(spawnDistance), offset(offset){}
		PickupType Type;
		float SpawnDistance;
		sf::Vector2f offset;
	};

	friend class Debug;

	void setup();
	void loadResources();
	static void handleCollisions();
	static std::unique_ptr<Aircraft> createAircraft(AircraftType type, sf::Vector2f position, NodeType nodeType, sf::Vector2f scale);
	void spawnEnemies();
	void spawnPickups();
	void addEnemies();
	void addPickUps();
	void guideMissiles();
	void adaptPlayerVelocity();
	void adaptPlayerPosition();
	static float m_scrollSpeed;

	sf::RenderWindow& m_window;
	sf::View m_worldView;
	EmptyWorldNode m_worldGraph;
	std::array<WorldNode*, static_cast<int>(Layer::LayerCount)> m_worldLayers{};
	sf::FloatRect m_worldBounds;
	std::vector<EnemySpawnPoint> m_enemySpawnPoints;
	std::vector<PickupSpawnPoint> m_pickupSpawnPoints;
	std::vector<Aircraft*> m_activeEnemies;
	sf::Vector2f m_spawnPosition;
	sf::Vector2f m_viewPositionOffset;
	Aircraft* m_playerAircraft;
	CommandQueue m_commandQueue;
};


#endif //WORLD_H_
