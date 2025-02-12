// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef WORLD_H_
#define WORLD_H_

#include <array>
#include <queue>
#include "GameSprite.h"
#include "Aircraft.h"
#include "Layer.h"
#include "EmptyWorldNode.h"
#include "CommandQueue.h"
#include "BloomEffect.h"
#include "CanvasNode.h"
#include "Audio.h"

class World
{
public:
	explicit World(sf::RenderTarget& outputTarget, Audio& audioPlayer);
	void render();
	CommandQueue& getCommandQueue() { return m_commandQueue; }
	static float getScrollSpeed() { return m_scrollSpeed; }
	static sf::View& getWorldView() { return m_worldView; }
	bool isPlayerAircraftExploding() const { return m_playerAircraft->isExploding(); }
	sf::FloatRect getViewBounds() const;
	sf::FloatRect getBattlefieldBounds() const;
	void destroyEntitiesOutsideView();
	void update(sf::Time deltaTime);
	static GameData GameData;
	bool isPlayerAlive() const { return m_isPlayerAlive; }
	bool hasPlayerReachedEnd() const { return m_hasPlayerReachedEnd; }
private:
	struct EnemySpawnPoint
	{
		EnemySpawnPoint(AircraftType type, float spawnDistance) : Type(type), SpawnDistance(spawnDistance){}
		AircraftType Type;
		float SpawnDistance;
	};

	struct PickupSpawnPoint
	{
		PickupSpawnPoint(PickupType type, float spawnDistance, sf::Vector2f offset) : Type(type), SpawnDistance(spawnDistance), Offset(offset){}
		PickupType Type;
		float SpawnDistance;
		sf::Vector2f Offset;
	};

	friend class Debug;

	void setup();
	void loadResources();
	void handleCollisions();
	static std::unique_ptr<Aircraft> createAircraft(AircraftType type, sf::Vector2f position, NodeType nodeType, sf::Vector2f scale);
	void spawnEnemies();
	void spawnPickups();
	void addEnemies();
	void addPickUps();
	void guideMissiles();
	void adaptPlayerVelocity();
	void adaptPlayerPosition();
	void updateSounds();
	static bool matchesCategories(WorldNode::Pair& colliders, NodeType t1, NodeType t2);

	static float m_scrollSpeed;
	static sf::View m_worldView;

	sf::RenderTarget& m_target;
	sf::RenderTexture m_sceneTexture;
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
	bool m_isPlayerAlive;
	bool m_hasPlayerReachedEnd;
	BloomEffect m_bloomEffect;
	CanvasNode* m_ui{};
	Audio& m_audioPlayer;

	sf::Text m_fpsText;
	float m_timeSinceLastFpsUpdate{};
	int m_framesSinceLastFpsUpdate{};
};


#endif //WORLD_H_
