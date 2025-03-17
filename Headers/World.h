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
#include "NetworkProtocol.h"

// Forward declaration
namespace sf
{
	class RenderTarget;
}
class NetworkNode;

//TODO: Preload textures
class World
{
public:
	explicit World(sf::RenderTarget& outputTarget, Audio& audioPlayer, bool isNetworked);
	void render();
	CommandQueue& getCommandQueue() { return m_commandQueue; }
	static float getScrollSpeed() { return m_scrollSpeed; }
	static sf::View& getWorldView() { return m_worldView; }
	sf::FloatRect getViewBounds() const;
	sf::FloatRect getBattlefieldBounds() const;
	void setWorldWidth(float width){ m_worldBounds.width = width;}
	void destroyEntitiesOutsideView();
	void update(sf::Time deltaTime);
	static GameData GameData;
	bool hasPlayerAlive() const { return !m_playerAircrafts.empty(); }
	bool hasPlayerReachedEnd() const;
	Aircraft* getAircraft(int identifier) const;
	void removeAircraft(int identifier);
	Aircraft* addAircraft(int identifier);
	bool pollGameAction(GameActions::Action& out);
	void setCurrentBattleFieldPosition(float lineX);
	void addEnemy(AircraftType type, float spawnDistance);
	void sortEnemies();
	void createPickUp(sf::Vector2f position, PickupType type);
	void setWorldScrollCompensation(float compensation);
 private:
	struct EnemySpawnPoint
	{
		EnemySpawnPoint(AircraftType type, float spawnDistance) : Type(type), SpawnDistance(spawnDistance){}
		AircraftType Type;
		float SpawnDistance;
	};

	friend class Debug;
	void setup();
	void loadResources();
	void handleCollisions();
	void spawnEnemies();
	void addEnemies();
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
	std::vector<Aircraft*> m_activeEnemies;
	sf::Vector2f m_spawnPosition;
	sf::Vector2f m_viewPositionOffset;
	CommandQueue m_commandQueue;
	BloomEffect m_bloomEffect;
	Audio& m_audioPlayer;
	std::vector<Aircraft*> m_playerAircrafts;
	sf::Text m_fpsText;
	float m_scrollSpeedCompensation{};
	bool m_isNetworkedWorld{};
	NetworkNode* m_networkNode{};
	CanvasNode* m_ui{};
	float m_timeSinceLastFpsUpdate{};
	int m_framesSinceLastFpsUpdate{};
};


#endif //WORLD_H_
