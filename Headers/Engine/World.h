// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file World.h
 * @brief Declaration of the World class.
 *
 * The World class encapsulates the game world. It is responsible for loading resources,
 * managing world entities (players, enemies, pickups, etc.), processing collisions, spawning enemies,
 * and handling world scrolling and rendering. The class also manages the game command queue and
 * integrates post-processing effects, audio, and network-related nodes.
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <array>
#include <queue>
#include "GameSprite.h"
#include "../Game/Aircraft.h"
#include "Layer.h"
#include "EmptyWorldNode.h"
#include "CommandQueue.h"
#include "BloomEffect.h"
#include "../Game/CanvasNode.h"
#include "Audio.h"
#include "NetworkProtocol.h"

namespace Engine
{
	class NetworkNode;
}

namespace AlphaSquadron
{

	/**
	 * @class World
	 * @brief Manages the game world.
	 *
	 * The World class handles rendering, updating entities, collision handling,
	 * enemy spawning, and world scrolling. It also provides a static interface to access
	 * global game data, view, and scroll speed.
	 */
	class World
	{
	 public:
		/**
		 * @brief Constructs the game world.
		 * @param outputTarget The render target used for drawing the scene.
		 * @param audioPlayer Reference to the audio system.
		 * @param isNetworked Flag indicating if the world is networked.
		 */
		explicit World(sf::RenderTarget& outputTarget, Engine::Audio& audioPlayer, bool isNetworked);

		/**
		 * @brief Renders the game world.
		 */
		void render();

		/**
		 * @brief Retrieves the command queue.
		 * @return Reference to the command queue.
		 */
		Engine::CommandQueue& getCommandQueue()
		{
			return m_commandQueue;
		}

		/**
		 * @brief Gets the current scroll speed.
		 * @return The scroll speed value.
		 */
		static float getScrollSpeed()
		{
			return m_scrollSpeed;
		}

		/**
		 * @brief Retrieves the current world view.
		 * @return Reference to the world view.
		 */
		static sf::View& getWorldView()
		{
			return m_worldView;
		}

		/**
		 * @brief Gets the bounds of the current view.
		 * @return A FloatRect representing the view bounds.
		 */
		sf::FloatRect getViewBounds() const;

		/**
		 * @brief Gets the bounds of the battlefield.
		 * @return A FloatRect representing the battlefield bounds.
		 */
		sf::FloatRect getBattlefieldBounds() const;

		/**
		 * @brief Sets the world width.
		 * @param width The new world width.
		 */
		void setWorldWidth(float width)
		{
			m_worldBounds.width = width;
		}

		/**
		 * @brief Removes entities that are outside the current view.
		 */
		void destroyEntitiesOutsideView();

		/**
		 * @brief Updates the world.
		 * @param deltaTime The elapsed time since the last update.
		 */
		void update(sf::Time deltaTime);

		/// Global game data loaded from a JSON file.
		static GameData GameData;

		/**
		 * @brief Checks if at least one player is still alive.
		 * @return True if a player aircraft exists; false otherwise.
		 */
		bool hasPlayerAlive() const
		{
			return !m_playerAircrafts.empty();
		}

		/**
		 * @brief Checks if the player has reached the end of the world.
		 * @return True if the player has left the world bounds; false otherwise.
		 */
		bool hasPlayerReachedEnd() const;

		/**
		 * @brief Retrieves a player aircraft by its identifier.
		 * @param identifier The unique identifier of the aircraft.
		 * @return Pointer to the aircraft, or nullptr if not found.
		 */
		Aircraft* getAircraft(int identifier) const;

		/**
		 * @brief Removes a player aircraft by its identifier.
		 * @param identifier The unique identifier of the aircraft.
		 */
		void removeAircraft(int identifier);

		/**
		 * @brief Adds a player aircraft to the world.
		 * @param identifier The unique identifier for the aircraft.
		 * @return Pointer to the newly added aircraft.
		 */
		Aircraft* addAircraft(int identifier, bool isLocal);

		/**
		 * @brief Polls for a game action from the network.
		 * @param out Reference to a GameActions::Action to populate.
		 * @return True if an action was available; false otherwise.
		 */
		bool pollGameAction(Engine::GameActions::Action& out);

		/**
		 * @brief Sets the current battlefield position.
		 * @param lineX The x-coordinate of the battlefield line.
		 */
		void setCurrentBattleFieldPosition(float lineX);

		/**
		 * @brief Adds an enemy spawn point.
		 * @param type The type of enemy aircraft.
		 * @param spawnDistance The distance at which the enemy should spawn.
		 */
		void addEnemy(AircraftType type, float spawnDistance);

		/**
		 * @brief Sorts the enemy spawn points.
		 */
		void sortEnemies();

		/**
		 * @brief Creates a pickup at a specified position.
		 * @param position The spawn position for the pickup.
		 * @param type The type of pickup.
		 */
		void createPickUp(sf::Vector2f position, PickupType type);

		/**
		 * @brief Sets the world scroll compensation factor.
		 * @param compensation The new compensation factor.
		 */
		void setWorldScrollCompensation(float compensation);

	 private:
		/**
		 * @struct EnemySpawnPoint
		 * @brief Represents a spawn point for an enemy.
		 */
		struct EnemySpawnPoint
		{
			/**
			 * @brief Constructs an EnemySpawnPoint.
			 * @param type The enemy aircraft type.
			 * @param spawnDistance The spawn distance.
			 */
			EnemySpawnPoint(AircraftType type, float spawnDistance) : Type(type), SpawnDistance(spawnDistance) {}
			AircraftType Type;   ///< The type of enemy aircraft.
			float SpawnDistance; ///< The spawn distance along the x-axis.
		};

		friend class Debug;

		/**
		 * @brief Performs initial world setup.
		 */
		void setup();

		/**
		 * @brief Loads world resources.
		 */
		void loadResources();

		/**
		 * @brief Handles collisions between world entities.
		 */
		void handleCollisions();

		/**
		 * @brief Spawns enemies based on spawn points.
		 */
		void spawnEnemies();

		/**
		 * @brief Adds enemies from the spawn point list.
		 */
		void addEnemies();

		/**
		 * @brief Guides missiles towards targets.
		 */
		void guideMissiles();

		/**
		 * @brief Adjusts the velocity of player aircraft.
		 */
		void adaptPlayerVelocity();

		/**
		 * @brief Adjusts the position of player aircraft to stay within bounds.
		 */
		void adaptPlayerPosition();

		/**
		 * @brief Updates the sound system based on the listener position.
		 */
		void updateSounds();

		/**
		 * @brief Checks if two colliding nodes match the given categories.
		 * @param colliders A pair of WorldNode pointers.
		 * @param t1 The first node category.
		 * @param t2 The second node category.
		 * @return True if the categories match, false otherwise.
		 */
		static bool matchesCategories(Engine::WorldNode::Pair& colliders, NodeType t1, NodeType t2);

		// Static members for world scrolling and view.
		static float m_scrollSpeed;
		static sf::View m_worldView;

		sf::RenderTarget& m_target;          ///< The render target for the world.
		sf::RenderTexture m_sceneTexture;      ///< Offscreen texture for post-processing.
		Engine::EmptyWorldNode m_worldGraph;           ///< Root node of the world scene graph.
		std::array<Engine::WorldNode*, static_cast<int>(Engine::Layer::LayerCount)> m_worldLayers{}; ///< Array of world layers.
		sf::FloatRect m_worldBounds;           ///< Bounds of the world.
		std::vector<EnemySpawnPoint> m_enemySpawnPoints; ///< List of enemy spawn points.
		std::vector<Aircraft*> m_activeEnemies;          ///< List of active enemy aircraft.
		sf::Vector2f m_spawnPosition;          ///< Position where players spawn.
		sf::Vector2f m_viewPositionOffset;     ///< Offset for the view position.
		Engine::CommandQueue m_commandQueue;           ///< Command queue for world actions.
		Engine::BloomEffect m_bloomEffect;             ///< Bloom effect for post-processing.
		Engine::Audio& m_audioPlayer;                  ///< Reference to the audio system.
		std::vector<Aircraft*> m_playerAircrafts; ///< List of player aircraft.
		std::vector<int> m_localPlayerIds; 		///< List of local player Ids.
		sf::Text m_fpsText;                    ///< Text for displaying FPS.
		float m_scrollSpeedCompensation{};     ///< Compensation factor for scrolling speed.
		bool m_isNetworkedWorld{};             ///< Flag indicating if the world is networked.
		Engine::NetworkNode* m_networkNode{};          ///< Pointer to the network node (if any).
		AlphaSquadron::CanvasNode* m_ui{};                    ///< Pointer to the UI node.
		float m_timeSinceLastFpsUpdate{};      ///< Time accumulator for FPS update.
		int m_framesSinceLastFpsUpdate{};      ///< Frame counter for FPS update.
	};
}
#endif //WORLD_H_
