// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file World.cpp
 * @brief Implementation of the World class.
 *
 * This source file implements the functions of the World class, including rendering,
 * updating world entities, handling collisions, enemy spawning, missile guidance,
 * player adaptation, and sound updating.
 */

#include "../Headers/World.h"
#include "../Headers/Pickup.h"
#include "../Headers/Engine.h"
#include "../Headers/ParticleSystemNode.h"
#include "../Headers/AudioNode.h"
#include "../Headers/NetworkNode.h"

namespace AlphaSquadron
{
	GameData World::GameData = LoadData("../DataFiles/gameData.json");
	sf::View World::m_worldView = {};
	float World::m_scrollSpeed = 500.0f;

	World::World(sf::RenderTarget& outputTarget, Engine::Audio& audioPlayer, bool isNetworked)
		: m_target(outputTarget),
		  m_audioPlayer(audioPlayer),
		  m_worldBounds(0, 0.0f, 10000.0f, m_worldView.getSize().y),
		  m_spawnPosition(0, m_worldView.getSize().y / 2),
		  m_playerAircrafts(),
		  m_viewPositionOffset(0, 0),
		  m_commandQueue(),
		  m_scrollSpeedCompensation(1.f),
		  m_isNetworkedWorld(isNetworked),
		  m_networkNode(),
		  m_ui(),
		  m_timeSinceLastFpsUpdate(),
		  m_framesSinceLastFpsUpdate()
	{
		// Set the world view to the default view.
		m_worldView = m_target.getDefaultView();
		// Create the scene texture for offscreen rendering.
		m_sceneTexture.create(m_target.getSize().x, m_target.getSize().y);
		setup();
	}

	void World::setWorldScrollCompensation(float compensation)
	{
		m_scrollSpeedCompensation = compensation;
	}

	void World::update(sf::Time deltaTime)
	{
		// Scroll the world view horizontally.
		m_worldView.move(m_scrollSpeed * deltaTime.asSeconds(), 0.f);

		// Update UI with player health and reset velocity.
		int count = 0;
		for (auto id : m_localPlayerIds)
		{
			m_ui->setHeath(getAircraft(id)->getHealth(), count == 0);
			getAircraft(id)->setVelocity(0, 0);
			count++;
		}

		// Remove entities outside the view.
		destroyEntitiesOutsideView();
		// Guide missiles towards targets.
		guideMissiles();

		// Process commands from the command queue.
		while (!m_commandQueue.isEmpty())
		{
			auto nextCommand = m_commandQueue.pop();
			m_worldGraph.onCommand(nextCommand, deltaTime);
		}

		adaptPlayerVelocity();
		handleCollisions();

		for(auto& a : m_playerAircrafts)
		{
			if(a->isMarkedForRemoval())
			{
				auto newEnd = std::remove_if(m_localPlayerIds.begin(), m_localPlayerIds.end(),[a](int id) { return id == a->getIdentifier(); });
				m_localPlayerIds.erase(newEnd, m_localPlayerIds.end());
			}
		}

		// Remove destroyed player aircraft.
		auto firstToRemove = std::remove_if(m_playerAircrafts.begin(), m_playerAircrafts.end(), std::mem_fn(&Aircraft::isMarkedForRemoval));
		m_playerAircrafts.erase(firstToRemove, m_playerAircrafts.end());

		// Remove destroyed nodes from the scene graph.
		m_worldGraph.removeDestroyed();

		// Spawn new enemies if needed.
		spawnEnemies();

		// Update the world graph hierarchy.
		m_worldGraph.updateHierarchy(deltaTime, m_commandQueue);
		adaptPlayerPosition();

		updateSounds();

		// Update FPS text for debugging.
		if (Engine::Debug::isDebuggingEnabled())
		{
			m_framesSinceLastFpsUpdate++;
			m_timeSinceLastFpsUpdate += deltaTime.asSeconds();
			if (Engine::Debug::isFpsVisible())
			{
				m_fpsText.setPosition(sf::Vector2f(0, 0));
			}
			if (m_timeSinceLastFpsUpdate > 0.1f)
			{
				auto value = std::to_string((int)(m_framesSinceLastFpsUpdate / m_timeSinceLastFpsUpdate));
				auto& view = getWorldView();
				sf::Vector2f center = view.getCenter();
				sf::Vector2f size = view.getSize();
				m_fpsText.setCharacterSize(15);
				Aircraft* player = getAircraft(1);
				sf::Vector2f playerPos = (player == nullptr) ? sf::Vector2f() : getAircraft(1)->getPosition();
				m_fpsText.setString("FPS: " + value + "View POS: (x= " + std::to_string((int)center.x + (int)size.x / 2) +
					" y= " + std::to_string((int)center.y) + ")" + "Player Pos: (x= " + std::to_string((int)playerPos.x) +
					" y= " + std::to_string((int)playerPos.y) + ")");
				m_timeSinceLastFpsUpdate = 0;
				m_framesSinceLastFpsUpdate = 0;
			}
		}
	}

	void World::render()
	{
		// If post effects are not supported, render to the scene texture and apply bloom.
		if (!Engine::PostEffect::isSupported())
		{
			m_sceneTexture.clear();
			m_sceneTexture.setView(m_worldView);
			m_sceneTexture.draw(m_worldGraph);
			m_sceneTexture.display();
			m_bloomEffect.apply(m_sceneTexture, m_target);
		}
		else
		{
			// Otherwise, draw the scene graph directly.
			m_target.setView(m_worldView);
			m_target.draw(m_worldGraph);
		}

		// If debugging and FPS display are enabled, draw the FPS text.
		if (Engine::Debug::isDebuggingEnabled() && Engine::Debug::isFpsVisible())
		{
			sf::View currentView = m_target.getView();
			sf::Vector2f viewCenter = currentView.getCenter();
			sf::Vector2f viewSize = currentView.getSize();
			sf::Vector2f topLeftPosition = sf::Vector2f(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);
			m_fpsText.setPosition(topLeftPosition);
			m_target.draw(m_fpsText);
		}
	}

	Aircraft* World::getAircraft(int identifier) const
	{
		// Search for a player aircraft with the matching identifier.
		for (Aircraft* a : m_playerAircrafts)
		{
			if (a->getIdentifier() == identifier)
				return a;
		}
		return nullptr;
	}

	void World::removeAircraft(int identifier)
	{
		// Find the aircraft and mark it for removal.
		Aircraft* aircraft = getAircraft(identifier);
		if (aircraft)
		{
			auto newEnd = std::remove_if(m_localPlayerIds.begin(), m_localPlayerIds.end(),[identifier](int id) { return id == identifier; });
			m_localPlayerIds.erase(newEnd, m_localPlayerIds.end());

			aircraft->destroy();
			m_playerAircrafts.erase(std::find(m_playerAircrafts.begin(), m_playerAircrafts.end(), aircraft));
		}
	}

	Aircraft* World::addAircraft(int identifier, bool isLocalPlayer)
	{
		// Create a new player aircraft at a calculated spawn position.
		std::unique_ptr<Aircraft> player(new Aircraft(NodeType::Player, AircraftType::Tomcat, m_worldView.getCenter(), sf::Vector2f(1, 1)));
		auto center = m_worldView.getCenter();
		auto sizeX = m_worldView.getSize().x / 2;
		player->setPosition(center.x - sizeX, center.y);
		player->setIdentifier(identifier);
		player->loadResources();
		m_playerAircrafts.push_back(player.get());
		if(isLocalPlayer)
			m_localPlayerIds.push_back(identifier);

		if(m_localPlayerIds.size() == 2)
			m_ui->addPlayer2Ui();

		// Attach the aircraft to the front sprite layer.
		m_worldLayers[static_cast<int>(Engine::Layer::SpriteFront)]->attachNode(std::move(player));
		return m_playerAircrafts.back();
	}

	void World::createPickUp(sf::Vector2f position, PickupType type)
	{
		// Create and initialize a pickup at the specified position.
		auto pickup = std::make_unique<Pickup>(type);
		pickup->setPosition(position);
		pickup->setVelocity(0.f, 1.f);
		pickup->loadHierarchyResources();
		m_worldLayers[static_cast<int>(Engine::Layer::SpriteFront)]->attachNode(std::move(pickup));
	}

	bool World::pollGameAction(Engine::GameActions::Action& out)
	{
		// Poll the network node for any game actions.
		return m_networkNode->pollGameAction(out);
	}

	void World::setCurrentBattleFieldPosition(float lineX)
	{
		// Adjust the world view center and spawn position based on the battlefield line.
		m_worldView.setCenter(lineX + m_worldView.getSize().x / 2, m_worldView.getCenter().y);
		m_spawnPosition.x = lineX;
	}

	bool World::hasPlayerReachedEnd() const
	{
		// Check if player aircraft has moved outside the world bounds.
		if (Aircraft* aircraft = getAircraft(1))
			return !m_worldBounds.contains(aircraft->getPosition());
		else
			return false;
	}

	void World::loadResources()
	{
		// Load resources for the world graph.
		m_worldGraph.loadHierarchyResources();
	}

	void World::adaptPlayerPosition()
	{
		// Constrain each player aircraft within the current view bounds.
		for (auto& a : m_playerAircrafts)
		{
			sf::FloatRect viewBounds(m_worldView.getCenter() - m_worldView.getSize() / 2.f, m_worldView.getSize());
			const auto spriteBounds = a->getBoundingRect();
			sf::Vector2f position = a->getPosition();
			position.x = std::max(position.x, viewBounds.left + spriteBounds.width / 2);
			position.x = std::min(position.x, viewBounds.left + viewBounds.width - spriteBounds.width / 2);
			position.y = std::max(position.y, viewBounds.top + spriteBounds.height / 2);
			position.y = std::min(position.y, viewBounds.top + viewBounds.height - spriteBounds.height / 2);
			a->setPosition(position);
		}
	}

	void World::adaptPlayerVelocity()
	{
		// Adjust the velocity of each player aircraft.
		for (auto& a : m_playerAircrafts)
		{
			sf::Vector2f velocity = a->getVelocity();
			if (velocity.x != 0.f && velocity.y != 0.f)
				a->setVelocity(velocity / std::sqrt(2.f));

			// Ensure that the player aircraft is accelerated by the scroll speed.
			a->accelerate(velocity.x >= 0 ? m_scrollSpeed : 0, 0.f);
		}
	}

	bool World::matchesCategories(Engine::WorldNode::Pair& colliders, NodeType t1, NodeType t2)
	{
		// Determine if the colliding nodes match the specified categories.
		auto type1 = static_cast<unsigned int>(t1);
		auto type2 = static_cast<unsigned int>(t2);

		unsigned int colliderNodeType1 = colliders.first->getNodeType();
		unsigned int colliderNodeType2 = colliders.second->getNodeType();

		if (type1 & colliderNodeType1 && type2 & colliderNodeType2)
		{
			return true;
		}
		else if (type1 & colliderNodeType2 && type2 & colliderNodeType1)
		{
			std::swap(colliders.first, colliders.second);
			return true;
		}
		else
		{
			return false;
		}
	}

	void World::handleCollisions()
	{
		// Detect and process collisions within the world.
		std::set<Engine::WorldNode::Pair> collisionPairs;
		m_worldGraph.checkWorldCollision(m_worldGraph, collisionPairs);
		for (Engine::WorldNode::Pair pair : collisionPairs)
		{
			if (matchesCategories(pair, NodeType::Player, NodeType::Enemy))
			{
				auto& player = dynamic_cast<Aircraft&>(*pair.first);
				auto& enemy = dynamic_cast<Aircraft&>(*pair.second);
				player.changeHealth(-enemy.getHealth());
				enemy.changeHealth(-player.getHealth());

				if (enemy.getHealth() <= 0)
				{
					m_audioPlayer.playSound(SoundFxId::Explosion, 50);
					if(!m_isNetworkedWorld && Engine::Utility::getRandomNumber(0, 3) == 0)
					{
						auto randPickup = Engine::Utility::getRandomNumber(0u, static_cast<unsigned int>(PickupType::PickupCount)-1);
						createPickUp(enemy.getPosition(), static_cast<PickupType>(randPickup));
					}
				}
				else
					m_audioPlayer.playSound(SoundFxId::TakeDamage, 50);

				if (player.getHealth() <= 0 || enemy.getHealth() <= 0)
					m_audioPlayer.playSound(SoundFxId::Explosion, 50);
				else
				{
					m_audioPlayer.playSound(SoundFxId::TakeDamage, 50);
					m_audioPlayer.playSound(SoundFxId::DamageWarning1, 20);
				}
			}
			else if (matchesCategories(pair, NodeType::Player, NodeType::Pickup))
			{
				auto& player = dynamic_cast<Aircraft&>(*pair.first);
				auto& pickup = dynamic_cast<Pickup&>(*pair.second);
				pickup.apply(player);
				pickup.destroy();
				pickup.markForRemoval();
				m_audioPlayer.playSound(SoundFxId::CollectPickup, 20);
			}
			else if (matchesCategories(pair, NodeType::Enemy, NodeType::AlliedProjectile) ||
				matchesCategories(pair, NodeType::Player, NodeType::EnemyProjectile))
			{
				auto& aircraft = dynamic_cast<Aircraft&>(*pair.first);
				auto& projectile = dynamic_cast<Projectile&>(*pair.second);
				aircraft.changeHealth(-projectile.getDamage());
				projectile.destroy();
				projectile.markForRemoval();

				if (aircraft.getHealth() <= 0)
				{
					m_audioPlayer.playSound(SoundFxId::Explosion, 50);

					if(!m_isNetworkedWorld && (static_cast<unsigned int>(NodeType::Enemy) & aircraft.getNodeType()) > 0 && Engine::Utility::getRandomNumber(0, 3) == 0)
					{
				 		auto randPickup = Engine::Utility::getRandomNumber(0u, static_cast<unsigned int>(PickupType::PickupCount)-1);
						createPickUp(aircraft.getPosition(), static_cast<PickupType>(randPickup));
					}
				}
				else
				{
					m_audioPlayer.playSound(SoundFxId::TakeDamage, 50);
					if (aircraft.getNodeType() & static_cast<unsigned int>(NodeType::Player))
					{
						m_audioPlayer.playSound(SoundFxId::DamageWarning1, 20);
					}
				}
			}
		}
	}

	void World::updateSounds()
	{
		// Determine the listener position based on player aircraft positions.
		sf::Vector2f listenerPosition;

		// Use the view center if no player aircraft are present.
		if (m_playerAircrafts.empty())
		{
			listenerPosition = m_worldView.getCenter();
		}
			// Otherwise, compute the mean position of all player aircraft.
		else
		{
			for (Aircraft* aircraft : m_playerAircrafts)
				listenerPosition += aircraft->getWorldPosition();
			listenerPosition /= static_cast<float>(m_playerAircrafts.size());
		}

		// Set the listener's position for the audio system.
		Engine::Audio::setListenerPosition(listenerPosition);
	}

	void World::setup()
	{
		// Set the world graph to be non-collidable.
		m_worldGraph.setIsCollidable(false);
		// Create and attach each layer node.
		for (int i = 0; i < static_cast<int>(Engine::Layer::LayerCount); ++i)
		{
			Engine::WorldNode::SmartNode layer(static_cast<Engine::Layer>(i) == Engine::Layer::SpriteFront ? new Engine::EmptyWorldNode(NodeType::SpriteFrontLayer) : new Engine::EmptyWorldNode());
			layer->setIsCollidable(static_cast<Engine::Layer>(i) == Engine::Layer::SpriteFront);
			m_worldLayers[i] = layer.get();
			m_worldGraph.attachNode(std::move(layer));
		}

		// Create and configure the background sprite.
		std::unique_ptr<Engine::GameSprite> backgroundSprite(
			new Engine::GameSprite(
				false,
				TextureId::DecayedCityBg,
				false,
				sf::IntRect(),
				sf::IntRect(),
				true));
		backgroundSprite->loadResources();
		backgroundSprite->setIsCollidable(false);
		backgroundSprite->setPosition(m_worldBounds.left - m_worldView.getSize().x, m_worldBounds.top);
		auto windowSize = m_target.getView().getSize();
		auto bgTextureSize = backgroundSprite->getTexture()->getSize();
		backgroundSprite->setSpriteTextureRegion(sf::IntRect(0, 0, 50000, bgTextureSize.y));
		backgroundSprite->setScale(windowSize.x / bgTextureSize.x, windowSize.y / bgTextureSize.y);
		m_worldLayers[static_cast<int>(Engine::Layer::Background)]->attachNode(std::move(backgroundSprite));

		// Create the UI canvas node.
		std::unique_ptr<AlphaSquadron::CanvasNode> ui = std::make_unique<AlphaSquadron::CanvasNode>();
		m_ui = ui.get();
		m_worldLayers[static_cast<int>(Engine::Layer::UI)]->attachNode(std::move(ui));

		// Create and attach particle system nodes for smoke and propellant effects.
		std::unique_ptr<Engine::ParticleSystemNode> smokeNode(new Engine::ParticleSystemNode(Smoke));
		m_worldLayers[static_cast<int>(Engine::Layer::SpriteBack)]->attachNode(std::move(smokeNode));

		std::unique_ptr<Engine::ParticleSystemNode> propellantNode(new Engine::ParticleSystemNode(Propellant));
		m_worldLayers[static_cast<int>(Engine::Layer::SpriteBack)]->attachNode(std::move(propellantNode));

		// Create and attach an audio node to play background music.
		std::unique_ptr<Engine::AudioNode> audioNode(new Engine::AudioNode(m_audioPlayer));
		audioNode->playMusic(MusicId::GameMusic, 10);
		m_worldLayers[static_cast<int>(Engine::Layer::Audio)]->attachNode(std::move(audioNode));

		// Load additional resources for the world.
		loadResources();
		m_worldView.setCenter(m_worldView.getSize().x / 2, m_worldView.getSize().y / 2);

		// If the world is networked, attach a network node.
		if (m_isNetworkedWorld)
		{
			std::unique_ptr<Engine::NetworkNode> networkNode(new Engine::NetworkNode());
			m_networkNode = networkNode.get();
			m_worldGraph.attachNode(std::move(networkNode));
		}

		// Add enemy spawn points.
		addEnemies();

		// Set up the FPS text for debugging.
		m_fpsText.setFont(ResourceManager::loadResource(Engine::FontId::Arnold));
		m_fpsText.setPosition(sf::Vector2f());
		m_fpsText.setStyle(sf::Text::Bold | sf::Text::Underlined);
		m_fpsText.setCharacterSize(100);
		m_fpsText.setFillColor(sf::Color::White);
		m_fpsText.setString("0000");
	}

	void World::addEnemies()
	{
		// Do not add enemies in networked mode.
		if (m_isNetworkedWorld)
			return;

		// Add predetermined enemy spawn points.
		m_enemySpawnPoints.emplace_back(AircraftType::Tomcat, 2500.f);
		m_enemySpawnPoints.emplace_back(AircraftType::Chopper, 3000.f);
		m_enemySpawnPoints.emplace_back(AircraftType::Chopper, 4000.f);
		m_enemySpawnPoints.emplace_back(AircraftType::Chopper, 4200.f);
		m_enemySpawnPoints.emplace_back(AircraftType::Tomcat, 6000.f);
		m_enemySpawnPoints.emplace_back(AircraftType::Chopper, 7000.f);
		sortEnemies();
	}

	void World::sortEnemies()
	{
		// Sort enemy spawn points by spawn distance in descending order.
		std::sort(m_enemySpawnPoints.begin(), m_enemySpawnPoints.end(),
			[](EnemySpawnPoint lhs, EnemySpawnPoint rhs)
			{
			  return lhs.SpawnDistance > rhs.SpawnDistance;
			});
	}

	void World::addEnemy(AircraftType type, float spawnDistance)
	{
		// Add a new enemy spawn point.
		EnemySpawnPoint spawn(type, spawnDistance);
		m_enemySpawnPoints.push_back(spawn);
	}

	void World::spawnEnemies()
	{
		// Retrieve battlefield bounds.
		auto bounds = getBattlefieldBounds();

		// Spawn enemies for spawn points that are within the battlefield bounds.
		while (!m_enemySpawnPoints.empty() && m_enemySpawnPoints.back().SpawnDistance < bounds.left + bounds.width)
		{
			EnemySpawnPoint spawn = m_enemySpawnPoints.back();
			auto enemy = std::make_unique<Aircraft>(NodeType::Enemy, spawn.Type, sf::Vector2f(spawn.SpawnDistance, 0), sf::Vector2f(-1.0, 1.0));
			enemy->loadHierarchyResources();
			m_worldLayers[static_cast<int>(Engine::Layer::SpriteFront)]->attachNode(std::move(enemy));
			m_enemySpawnPoints.pop_back();
		}
	}

	void World::destroyEntitiesOutsideView()
	{
		// Create a command to destroy projectiles, pickups, and enemies outside the battlefield bounds.
		Engine::Command command;
		command.NodeType = static_cast<unsigned int>(NodeType::EnemyProjectile) |
			static_cast<unsigned int>(NodeType::AlliedProjectile) |
			static_cast<unsigned int>(NodeType::Pickup) |
			static_cast<unsigned int>(NodeType::Enemy);

		command.Action = Engine::DerivedAction<Engine::GameSprite>(
			[this](Engine::GameSprite& e, sf::Time)
			{
			  if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
			  {
				  e.destroy();
				  e.markForRemoval();
			  }
			});

		m_commandQueue.push(command);
	}

	void World::guideMissiles()
	{
		// Collect active enemy aircraft.
		Engine::Command enemyCollector;
		enemyCollector.NodeType |= (int)NodeType::Enemy;
		enemyCollector.Action =
			Engine::DerivedAction<Aircraft>([this](Aircraft& enemy, sf::Time dt)
			{
			  if (!enemy.isDestroyed())
				  m_activeEnemies.push_back(&enemy);
			});
		m_commandQueue.push(enemyCollector);

		// Guide guided missiles towards the closest enemy.
		Engine::Command missileGuider;
		missileGuider.NodeType |= (int)NodeType::AlliedProjectile;
		missileGuider.Action =
			Engine::DerivedAction<Projectile>(
				[this](Projectile& missile, sf::Time dt)
				{
				  if (!missile.isGuided())
					  return;

				  float minDistance = std::numeric_limits<float>::max();
				  Aircraft* closestEnemy = nullptr;
				  for (Aircraft* enemy : m_activeEnemies)
				  {
					  float enemyDistance = Engine::Utility::getDistance(missile, *enemy);
					  if (enemyDistance < minDistance)
					  {
						  closestEnemy = enemy;
						  minDistance = enemyDistance;
					  }
				  }
				  if (closestEnemy)
					  missile.guideTowards(sf::Vector2f(closestEnemy->getWorldPosition().x +
							  (closestEnemy->getScale().x * closestEnemy->getBoundingRect().width) / 2,
						  closestEnemy->getWorldPosition().y));
				});
		m_commandQueue.push(missileGuider);
		m_activeEnemies.clear();
	}

	sf::FloatRect World::getViewBounds() const
	{
		// Calculate view bounds based on the world view's center and size.
		return {m_worldView.getCenter() - m_worldView.getSize() / 2.f, m_worldView.getSize()};
	}

	sf::FloatRect World::getBattlefieldBounds() const
	{
		// Extend the view bounds slightly for the battlefield.
		sf::FloatRect bounds = getViewBounds();
		bounds.width += 100.f;
		return bounds;
	}
}