// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/World.h"
#include "../Headers/Audio.h"
#include "../Headers/Pickup.h"
#include "../Headers/Engine.h"
#include "../Headers/ParticleSystemNode.h"
#include "../Headers/AudioNode.h"
#include "../Headers/NetworkNode.h"

GameData World::GameData = LoadData("../DataFiles/gameData.json");
sf::View World::m_worldView = {};
float World::m_scrollSpeed = 500.0f;

World::World(sf::RenderTarget& outputTarget, Audio& audioPlayer, bool isNetworked) : m_target(outputTarget), m_audioPlayer(audioPlayer),
																	m_worldBounds(0.0f,0.0f,100000.0f,m_worldView.getSize().y),
																	m_spawnPosition(0, m_worldView.getSize().y/2),
																	m_playerAircrafts(), m_viewPositionOffset(0,0), m_commandQueue(),
																	m_scrollSpeedCompensation(1.f),
																	m_isNetworkedWorld(isNetworked),
																	m_networkNode(),
																	m_ui(),
																	m_timeSinceLastFpsUpdate(),
																	m_framesSinceLastFpsUpdate()
{
	m_worldView = m_target.getDefaultView();
	m_sceneTexture.create(m_target.getSize().x, m_target.getSize().y);
	setup();
}

void World::setWorldScrollCompensation(float compensation)
{
	m_scrollSpeedCompensation = compensation;
}

void World::update(sf::Time deltaTime)
{
	/*if(m_playerAircraft->isDestroyed())
	{
		m_isPlayerAlive = false;
	}

	m_ui->setHeath(m_playerAircraft->getHealth());

	if(m_worldView.getCenter().x > 15000.0f)
	{
		m_hasPlayerReachedEnd = true;
		return;
	}*/

	m_worldView.move(m_scrollSpeed * deltaTime.asSeconds(), 0.f);

	for(auto& a : m_playerAircrafts)
		a->setVelocity(0,0);

	destroyEntitiesOutsideView();
	guideMissiles();

	while (!m_commandQueue.isEmpty())
	{
		auto nextCommand = m_commandQueue.pop();
		m_worldGraph.onCommand(nextCommand, deltaTime);
	}

	adaptPlayerVelocity();
	handleCollisions();

	// Remove aircrafts that were destroyed (World::removeWrecks() only destroys the entities, not the pointers in mPlayerAircraft)
	auto firstToRemove = std::remove_if(m_playerAircrafts.begin(), m_playerAircrafts.end(), std::mem_fn(&Aircraft::isMarkedForRemoval));
	m_playerAircrafts.erase(firstToRemove, m_playerAircrafts.end());

	m_worldGraph.removeDestroyed();

	spawnEnemies();

	m_worldGraph.updateHierarchy(deltaTime, m_commandQueue);
	adaptPlayerPosition();

	updateSounds();

	if(Debug::isDebuggingEnabled())
	{
		m_framesSinceLastFpsUpdate++;
		m_timeSinceLastFpsUpdate += deltaTime.asSeconds();
		if(Debug::isFpsVisible())
		{
			m_fpsText.setPosition(sf::Vector2f(0,0));
		}
		if(m_timeSinceLastFpsUpdate > 1)
		{
			auto value = std::to_string((int)(m_framesSinceLastFpsUpdate/m_timeSinceLastFpsUpdate));
			auto& view = getWorldView();
			sf::Vector2f center = view.getCenter();
			sf::Vector2f size = view.getSize();
			m_fpsText.setString("FPS: " + value + " POS: (x= " + std::to_string(center.x + size.x / 2.f) +  + " y= " + std::to_string(center.y) + ")");
			m_timeSinceLastFpsUpdate = 0;
			m_framesSinceLastFpsUpdate = 0;
		}
	}
}

void World::render()
{
	if(!PostEffect::isSupported())
	{
		m_sceneTexture.clear();
		m_sceneTexture.setView(m_worldView);
		m_sceneTexture.draw(m_worldGraph);
		m_sceneTexture.display();
		m_bloomEffect.apply(m_sceneTexture, m_target);
	}
	else
	{
		m_target.setView(m_worldView);
		m_target.draw(m_worldGraph);
	}


	if(Debug::isDebuggingEnabled() && Debug::isFpsVisible())
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
	for(Aircraft* a : m_playerAircrafts)
	{
		if (a->getIdentifier() == identifier)
			return a;
	}

	return nullptr;
}



void World::removeAircraft(int identifier)
{
	Aircraft* aircraft = getAircraft(identifier);
	if (aircraft)
	{
		aircraft->destroy();
		m_playerAircrafts.erase(std::find(m_playerAircrafts.begin(), m_playerAircrafts.end(), aircraft));
	}
}

Aircraft* World::addAircraft(int identifier)
{
	std::unique_ptr<Aircraft> player(new Aircraft(NodeType::Player, AircraftType::Tomcat, sf::Vector2f(1,1), m_worldView.getCenter()));
	player->setPosition(m_worldView.getCenter());
	player->setIdentifier(identifier);
	player->loadResources();
	m_playerAircrafts.push_back(player.get());

	m_worldLayers[static_cast<int>(Layer::SpriteFront)]->attachNode(std::move(player));
	return m_playerAircrafts.back();
}

void World::createPickUp(sf::Vector2f position, PickupType type)
{
	auto pickup = std::make_unique<Pickup>(type);
	pickup->setPosition(position);
	pickup->setVelocity(0.f, 1.f);
	pickup->loadHierarchyResources();
	m_worldLayers[static_cast<int>(Layer::SpriteFront)]->attachNode(std::move(pickup));
}

bool World::pollGameAction(GameActions::Action& out)
{
	return m_networkNode->pollGameAction(out);
}
void World::setCurrentBattleFieldPosition(float lineX)
{
	m_worldView.setCenter(m_worldView.getCenter().x, lineX - m_worldView.getSize().y/2);
	m_spawnPosition.y = m_worldBounds.height;
}

bool World::hasPlayerReachedEnd() const
{
	if (Aircraft* aircraft = getAircraft(1))
		return !m_worldBounds.contains(aircraft->getPosition());
	else
		return false;
}

void World::loadResources()
{
	m_worldGraph.loadHierarchyResources();
}

void World::adaptPlayerPosition()
{
	for(auto& a : m_playerAircrafts)
	{
		sf::FloatRect viewBounds(m_worldView.getCenter() - m_worldView.getSize() / 2.f,m_worldView.getSize());
		const auto spriteBounds = a->getBoundingRect();
		sf::Vector2f position = a->getPosition();
		position.x = std::max(position.x, viewBounds.left + spriteBounds.width/2);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - spriteBounds.width/2);
		position.y = std::max(position.y, viewBounds.top + spriteBounds.height/2);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - spriteBounds.height/2);
		a->setPosition(position);
	}

}

void World::adaptPlayerVelocity()
{
	for(auto& a : m_playerAircrafts)
	{
		sf::Vector2f velocity = a->getVelocity();
		if (velocity.x != 0.f && velocity.y != 0.f)
			a->setVelocity(velocity / std::sqrt(2.f));

		a->accelerate(velocity.x >= 0 ? m_scrollSpeed : 0, 0.f);
	}

}

bool World::matchesCategories(WorldNode::Pair& colliders, NodeType t1, NodeType t2)
{
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
	std::set<WorldNode::Pair> collisionPairs;
	m_worldGraph.checkWorldCollision(m_worldGraph, collisionPairs);
	for(WorldNode::Pair pair : collisionPairs)
	{
		if (matchesCategories(pair, NodeType::Player, NodeType::Enemy))
		{
			auto& player = dynamic_cast<Aircraft&>(*pair.first);
			auto& enemy = dynamic_cast<Aircraft&>(*pair.second);
			player.changeHealth(-enemy.getHealth());
			enemy.changeHealth(-player.getHealth());
			if(player.getHealth() <= 0)
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

			if(aircraft.getHealth() <= 0)
				m_audioPlayer.playSound(SoundFxId::Explosion, 50);
			else
			{
				m_audioPlayer.playSound(SoundFxId::TakeDamage, 50);
				if(aircraft.getNodeType() & static_cast<unsigned int>(NodeType::Player))
				{
					m_audioPlayer.playSound(SoundFxId::DamageWarning1, 20);
				}

			}
		}
	}
}

void World::updateSounds()
{

	sf::Vector2f listenerPosition;

	// 0 players (multiplayer mode, until server is connected) -> view center
	if (m_playerAircrafts.empty())
	{
		listenerPosition = m_worldView.getCenter();
	}

		// 1 or more players -> mean position between all aircrafts
	else
	{
		for(Aircraft* aircraft : m_playerAircrafts)
			listenerPosition += aircraft->getWorldPosition();
		listenerPosition /= static_cast<float>(m_playerAircrafts.size());
	}

	// Set listener's position
	Audio::setListenerPosition(listenerPosition);
}

void World::setup()
{
	m_worldGraph.setIsCollidable(false);
	for (int i = 0; i < static_cast<int>(Layer::LayerCount); ++i)
	{
		WorldNode::SmartNode layer(static_cast<Layer>(i) == Layer::SpriteFront ? new EmptyWorldNode(NodeType::SpriteFrontLayer) : new EmptyWorldNode());
		layer->setIsCollidable(static_cast<Layer>(i) == Layer::SpriteFront);
		m_worldLayers[i] = layer.get();
		m_worldGraph.attachNode(std::move(layer));
	}

	std::unique_ptr<GameSprite> backgroundSprite(
		new GameSprite(
			false,
			TextureId::DecayedCityBg,
			false,
			sf::IntRect(),
			sf::IntRect(),
			true));
	backgroundSprite->loadResources();
	backgroundSprite->setIsCollidable(false);
	backgroundSprite->setPosition( m_worldBounds.left - m_worldView.getSize().x, m_worldBounds.top);
	auto windowSize = m_target.getView().getSize();
	auto bgTextureSize = backgroundSprite->getTexture()->getSize();
	backgroundSprite->setSpriteTextureRegion(sf::IntRect(0, 0, m_worldBounds.width, bgTextureSize.y));
	backgroundSprite->setScale(windowSize.x/bgTextureSize.x, windowSize.y/bgTextureSize.y);
	m_worldLayers[static_cast<int>(Layer::Background)]->attachNode(std::move(backgroundSprite));

	std::unique_ptr<CanvasNode> ui = std::make_unique<CanvasNode>();
	m_ui = ui.get();
	m_worldLayers[static_cast<int>(Layer::UI)]->attachNode(std::move(ui));

	std::unique_ptr<ParticleSystemNode> smokeNode(new ParticleSystemNode(Particle::Smoke));
	m_worldLayers[static_cast<int>(Layer::SpriteBack)]->attachNode(std::move(smokeNode));

	std::unique_ptr<ParticleSystemNode> propellantNode(new ParticleSystemNode(Particle::Propellant));
	m_worldLayers[static_cast<int>(Layer::SpriteBack)]->attachNode(std::move(propellantNode));

	std::unique_ptr<AudioNode> audioNode(new AudioNode(m_audioPlayer));
	audioNode->playMusic(MusicId::GameMusic, 10);
	m_worldLayers[static_cast<int>(Layer::Audio)]->attachNode(std::move(audioNode));

	loadResources();
	m_worldView.setCenter(m_spawnPosition);

	if (m_isNetworkedWorld)
	{
		std::unique_ptr<NetworkNode> networkNode(new NetworkNode());
		m_networkNode = networkNode.get();
		m_worldGraph.attachNode(std::move(networkNode));
	}

	addEnemies();

	m_fpsText.setFont(ResourceManager::loadResource(FontId::Arnold));
	m_fpsText.setPosition(sf::Vector2f());
	m_fpsText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_fpsText.setCharacterSize(100);
	m_fpsText.setFillColor(sf::Color::White);
	m_fpsText.setString("0000");
}

void World::addEnemies()
{
	if(m_isNetworkedWorld)
		return;

	m_enemySpawnPoints.emplace_back(AircraftType::Tomcat, 3500.f);
	m_enemySpawnPoints.emplace_back(AircraftType::Chopper, 5500.f);
	m_enemySpawnPoints.emplace_back(AircraftType::Chopper, 7000.f);
	m_enemySpawnPoints.emplace_back(AircraftType::Chopper, 9000.f);
	m_enemySpawnPoints.emplace_back(AircraftType::Tomcat, 12000.f);
	m_enemySpawnPoints.emplace_back(AircraftType::Chopper, 15000.f);
	sortEnemies();
}

void World::sortEnemies()
{
	std::sort(m_enemySpawnPoints.begin(), m_enemySpawnPoints.end(),
		[] (EnemySpawnPoint lhs, EnemySpawnPoint rhs)
		{
		  return lhs.SpawnDistance > rhs.SpawnDistance;
		});
}

void World::addEnemy(AircraftType type, float spawnDistance)
{
	EnemySpawnPoint spawn(type, spawnDistance);
	m_enemySpawnPoints.push_back(spawn);
}
void World::spawnEnemies()
{
	auto bounds = getBattlefieldBounds();

	while (!m_enemySpawnPoints.empty() && m_enemySpawnPoints.back().SpawnDistance < bounds.left + bounds.width)
	{
		EnemySpawnPoint spawn = m_enemySpawnPoints.back();
		auto enemy = std::make_unique<Aircraft>(NodeType::Enemy, spawn.Type, sf::Vector2f(spawn.SpawnDistance,0), sf::Vector2f(-1.0, 1.0));
		enemy->loadHierarchyResources();
		m_worldLayers[static_cast<int>(Layer::SpriteFront)]->attachNode(std::move(enemy));
		m_enemySpawnPoints.pop_back();
	}
}


void World:: destroyEntitiesOutsideView()
{
	Command command;
	command.NodeType = static_cast<unsigned int>(NodeType::EnemyProjectile) |
		static_cast<unsigned int>(NodeType::AlliedProjectile) |
		static_cast<unsigned int>(NodeType::Pickup) |
		static_cast<unsigned int>(NodeType::Enemy);

	command.Action = DerivedAction<GameSprite>(
		[this](GameSprite& e, sf::Time)
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
	Command enemyCollector;
	enemyCollector.NodeType |= (int)NodeType::Enemy;
	enemyCollector.Action =
		DerivedAction<Aircraft>([this](Aircraft& enemy, sf::Time dt)
		{
		  if (!enemy.isDestroyed())
			  m_activeEnemies.push_back(&enemy);
		});
	m_commandQueue.push(enemyCollector);


	Command missileGuider;
	missileGuider.NodeType |= (int)NodeType::AlliedProjectile;
	missileGuider.Action =
		DerivedAction<Projectile>(
			[this](Projectile& missile, sf::Time dt)
			{
			  if (!missile.isGuided())
				  return;

			  float minDistance = std::numeric_limits<float>::max();
			  Aircraft* closestEnemy = nullptr;
			  for (Aircraft* enemy : m_activeEnemies)
			  {
				  float enemyDistance = Utility::getDistance(missile, *enemy);
				  if (enemyDistance < minDistance)
				  {
					  closestEnemy = enemy;
					  minDistance = enemyDistance;
				  }
			  }
			  if (closestEnemy)
				  missile.guideTowards(sf::Vector2f(closestEnemy->getWorldPosition().x
						  + (closestEnemy->getScale().x * closestEnemy->getBoundingRect().width) / 2,
					  closestEnemy->getWorldPosition().y));
			});
	m_commandQueue.push(missileGuider);
	m_activeEnemies.clear();
}

sf::FloatRect World::getViewBounds() const
{
	return {m_worldView.getCenter() - m_worldView.getSize() / 2.f, m_worldView.getSize()};
}

sf::FloatRect World::getBattlefieldBounds() const
{
	sf::FloatRect bounds = getViewBounds();
	bounds.width += 100.f;
	return bounds;
}









