//
// Created by Johnnie Otis on 5/30/24.
//

#include "World.h"
#include "Tomcat.h"
#include "Audio.h"
#include "GameText.h"
#include "Chopper.h"
#include "Projectile.h"
#include "Pickup.h"
#include "Engine.h"

float World::m_scrollSpeed = 500.0f;
GameData World::GameData = LoadData("../DataFiles/gameData.json");

World::World(sf::RenderWindow& window) : m_window(window), m_worldView(window.getDefaultView()),
			m_worldBounds(0.0f,0.0f,100000.0f,m_worldView.getSize().y),
			m_spawnPosition(0, m_worldView.getSize().y/2),
			m_playerAircraft(nullptr), m_viewPositionOffset(0,0), m_commandQueue()
{
	setup();
	loadResources();
}

void World::restart()
{
	Audio::stopMusic();
	ResourceManager::clearFontCache();
	ResourceManager::clearSoundBufferCache();
	ResourceManager::clearTextureCache();
	setup();
	Debug::log("Restarting game.....");
}

void World:: destroyEntitiesOutsideView()
{
	Command command;
	command.NodeType = static_cast<unsigned int>(NodeType::EnemyProjectile) |
		static_cast<unsigned int>(NodeType::AlliedProjectile) |
		static_cast<unsigned int>(NodeType::Pickup) |
		static_cast<unsigned int>(NodeType::Enemy);

	command.Action = DerivedAction<Entity>(
		[this](Entity& e, float)
		{
		  if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
		  {
			  e.destroy();
			  e.markForRemoval();
		  }
		});

	m_commandQueue.push(command);
}

void World::setup()
{
	for (int i = 0; i < static_cast<int>(Layer::LayerCount); ++i)
	{
		WorldNode::SmartNode layer(static_cast<Layer>(i) == Layer::Collision ?  new EmptyWorldNode(NodeType::CollisionLayer) : new EmptyWorldNode());
		m_worldLayers[i] = layer.get();
		m_worldGraph.attachNode(std::move(layer));
	}

	std::unique_ptr<GameSprite> backgroundSkySprite(
		new GameSprite(
			false,
			TextureId::SmoggySky,
			false,
			sf::IntRect(),
			sf::IntRect(0,0,m_worldBounds.width, m_worldView.getSize().y),
			true));
	backgroundSkySprite->setPosition(m_worldBounds.left,m_worldBounds.top);
	backgroundSkySprite->setColor(sf::Color(90,89,255,255));
	m_worldLayers[static_cast<int>(Layer::Background)]->attachNode(std::move(backgroundSkySprite));

	std::unique_ptr<GameSprite> backgroundBuildingsSprite(
		new GameSprite(
			false,
			TextureId::DecayedBuildings1,
			false,
			sf::IntRect(),
			sf::IntRect(0,0,m_worldBounds.width,m_worldView.getSize().y),
			true));
	backgroundBuildingsSprite->setPosition(m_worldBounds.left,m_worldBounds.top);
	backgroundBuildingsSprite->setColor(sf::Color(155,155,155,55));
	m_worldLayers[static_cast<int>(Layer::Background)]->attachNode(std::move(backgroundBuildingsSprite));

	std::unique_ptr<Aircraft> player = createAircraft(AircraftType::Tomcat, m_spawnPosition, NodeType::Player, sf::Vector2f(4.0, 4.0));
	m_playerAircraft = player.get();
	m_playerAircraft->setVelocity(m_scrollSpeed, 0);
	m_worldLayers[static_cast<int>(Layer::Collision)]->attachNode(std::move(player));

	addEnemies();
	addPickUps();

	Audio::playMusic(MusicId::UNSquadronLevel1, 10);

	//Debug////////////////////////////////////////////////////////////////
	m_fpsText.setFont(ResourceManager::loadResource(FontId::Gamer));
	m_fpsText.setPosition(sf::Vector2f());
	m_fpsText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_fpsText.setCharacterSize(100);
	m_fpsText.setFillColor(sf::Color::White);
	m_fpsText.setString("0000");
	//////////////////////////////////////////////////////////////////////
}

void World::addEnemies()
{
	m_enemySpawnPoints.emplace_back(AircraftType::Tomcat, 5500.f);
	m_enemySpawnPoints.emplace_back(AircraftType::Chopper, 9000.f);

	std::sort(m_enemySpawnPoints.begin(), m_enemySpawnPoints.end(),
		[] (EnemySpawnPoint lhs, EnemySpawnPoint rhs)
		{
		  return lhs.SpawnDistance > rhs.SpawnDistance;
		});
}

void World::addPickUps()
{
	m_pickupSpawnPoints.emplace_back(PickupType::HealthRefill, 2000.f, sf::Vector2f(0, 100));
	m_pickupSpawnPoints.emplace_back(PickupType::FireRate, 3000.f, sf::Vector2f(0, 400));
	m_pickupSpawnPoints.emplace_back(PickupType::FireSpread, 4000.f, sf::Vector2f(0, 800));
	m_pickupSpawnPoints.emplace_back(PickupType::MissileRefill, 5000.f, sf::Vector2f(0, 200));

	std::sort(m_pickupSpawnPoints.begin(), m_pickupSpawnPoints.end(),
		[] (PickupSpawnPoint lhs, PickupSpawnPoint rhs)
		{
		  return lhs.SpawnDistance > rhs.SpawnDistance;
		});
}

void World::guideMissiles()
{
	Command enemyCollector;
	enemyCollector.NodeType |= (int)NodeType::Enemy;
	enemyCollector.Action =
		DerivedAction<Aircraft>([this](Aircraft& enemy, float dt)
		{
		  if (!enemy.isDestroyed())
			  m_activeEnemies.push_back(&enemy);
		});
	m_commandQueue.push(enemyCollector);


	Command missileGuider;
	missileGuider.NodeType |= (int)NodeType::AlliedProjectile;
	missileGuider.Action =
		DerivedAction<Projectile>(
			[this](Projectile& missile, float dt)
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
						  + (closestEnemy->getScale().x * closestEnemy->getGlobalBounds().width) / 2,
					  closestEnemy->getWorldPosition().y));
			});
	m_commandQueue.push(missileGuider);
	m_activeEnemies.clear();
}

void World::spawnEnemies()
{
	auto bounds = getBattlefieldBounds();

	while (!m_enemySpawnPoints.empty() && m_enemySpawnPoints.back().SpawnDistance < bounds.left + bounds.width)
	{
		EnemySpawnPoint spawn = m_enemySpawnPoints.back();
		auto enemy = createAircraft(spawn.Type, sf::Vector2f(spawn.SpawnDistance,0), NodeType::Enemy, sf::Vector2f(-4.0, 4.0));
		enemy->loadHierarchyResources();
		m_worldLayers[static_cast<int>(Layer::Collision)]->attachNode(std::move(enemy));
		m_enemySpawnPoints.pop_back();
	}
}

void World::spawnPickups()
{
	auto bounds = getBattlefieldBounds();

	while (!m_pickupSpawnPoints.empty() && m_pickupSpawnPoints.back().SpawnDistance < bounds.left + bounds.width)
	{
		PickupSpawnPoint spawn = m_pickupSpawnPoints.back();
		auto pickup = std::make_unique<Pickup>(spawn.Type);
		pickup->setPosition(sf::Vector2f(spawn.SpawnDistance + spawn.Offset.x, spawn.Offset.y));
		pickup->loadHierarchyResources();
		m_worldLayers[static_cast<int>(Layer::Collision)]->attachNode(std::move(pickup));
		m_pickupSpawnPoints.pop_back();
	}
}

std::unique_ptr<Aircraft> World::createAircraft(AircraftType type, sf::Vector2f position, NodeType nodeType, sf::Vector2f scale)
{
	switch(type)
	{
	case AircraftType::Chopper:
		return std::make_unique<Chopper>(true, position, nodeType, scale);
	case AircraftType::Tomcat:
		return std::make_unique<Tomcat>(true, position, nodeType, scale);
	default:
		return nullptr;
	}
}

//TODO: Add grid based collision detection
void World::handleCollisions()
{
	std::set<WorldNode::Pair> collisionPairs;
	m_worldGraph.checkWorldCollision(m_worldGraph, collisionPairs);
	for(WorldNode::Pair pair : collisionPairs)
	{
		if (matchesCategories(pair, NodeType::Player, NodeType::Enemy))
		{
			auto& player = static_cast<Aircraft&>(*pair.first);
			auto& enemy = static_cast<Aircraft&>(*pair.second);
			player.changeHealth(-enemy.getHealth());
			enemy.destroy();
			enemy.markForRemoval();
		}
		else if (matchesCategories(pair, NodeType::Player, NodeType::Pickup))
		{
			auto& player = static_cast<Aircraft&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);
			pickup.apply(player);
			pickup.destroy();
			pickup.markForRemoval();
		}
		else if (matchesCategories(pair, NodeType::Enemy, NodeType::AlliedProjectile) ||
					matchesCategories(pair, NodeType::Player, NodeType::EnemyProjectile))
		{
			auto& aircraft = static_cast<Aircraft&>(*pair.first);
			auto& projectile = static_cast<Projectile&>(*pair.second);
			aircraft.changeHealth(-projectile.getDamage());
			projectile.destroy();
			projectile.markForRemoval();
		}
	}
}

bool World::matchesCategories(WorldNode::Pair& colliders, NodeType t1, NodeType t2)
{
	unsigned int type1 = static_cast<unsigned int>(t1);
	unsigned int type2 = static_cast<unsigned int>(t2);

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

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(m_worldView.getCenter() - m_worldView.getSize() / 2.f, m_worldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const
{
	sf::FloatRect bounds = getViewBounds();
	bounds.width += 100.f;
	return bounds;
}

void World::loadResources()
{
	m_worldGraph.loadHierarchyResources();
}

void World::update(float deltaTime)
{
	if(!m_playerAircraft)
		Player::setMissionStatus(Player::MissionStatus::Failure);

	float scrollSpeedFactor = 1;
	m_worldView.move(m_scrollSpeed * scrollSpeedFactor * deltaTime, 0.f);

	if(m_playerAircraft)
		m_playerAircraft->setVelocity(0,0);

	destroyEntitiesOutsideView();
	guideMissiles();
	while (!m_commandQueue.isEmpty())
	{
		auto nextCommand = m_commandQueue.pop();
		m_worldGraph.onCommand(nextCommand, deltaTime);
	}

	if(m_playerAircraft)
		adaptPlayerVelocity();

	handleCollisions();
	m_worldGraph.removeDestroyed();
	if(m_playerAircraft && m_playerAircraft->isDestroyed())
	{
		m_playerAircraft->markForRemoval();
		m_playerAircraft->removeDestroyed();
		m_playerAircraft = nullptr;
	}
	spawnEnemies();
	spawnPickups();

	m_worldGraph.updateHierarchy(deltaTime, m_commandQueue);
	if(m_playerAircraft)
		adaptPlayerPosition();

	if(Debug::isDebuggingEnabled())
	{
		m_framesSinceLastFpsUpdate++;
		m_timeSinceLastFpsUpdate += deltaTime;
		if(Debug::isFpsVisible())
		{
			m_fpsText.setPosition(sf::Vector2f(0,0));
		}
		if(m_timeSinceLastFpsUpdate > 1)
		{
			auto value = std::to_string((int)(m_framesSinceLastFpsUpdate/m_timeSinceLastFpsUpdate));
			auto& view = Engine::getWindow().getView();
			sf::Vector2f center = view.getCenter();
			sf::Vector2f size = view.getSize();
			m_fpsText.setString("FPS: " + value + " POS: (x= " + std::to_string(center.x + size.x / 2.f) +  + " y= " + std::to_string(center.y) + ")");
			m_timeSinceLastFpsUpdate = 0;
			m_framesSinceLastFpsUpdate = 0;
		}
	}
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = m_playerAircraft->getVelocity();
	if (velocity.x != 0.f && velocity.y != 0.f)
		m_playerAircraft->setVelocity(velocity / std::sqrt(2.f));

	m_playerAircraft->accelerate(m_scrollSpeed, 0.f);
}

void World::adaptPlayerPosition()
{
	if(m_playerAircraft)
	{
		sf::FloatRect viewBounds(m_worldView.getCenter() - m_worldView.getSize() / 2.f,m_worldView.getSize());
		const auto spriteBounds = m_playerAircraft->getGlobalBounds();
		sf::Vector2f position = m_playerAircraft->getPosition();
		position.x = std::max(position.x, viewBounds.left + 0);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - spriteBounds.width);
		position.y = std::max(position.y, viewBounds.top + 0);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - spriteBounds.height);
		m_playerAircraft->setPosition(position);
	}
}

void World::render(sf::RenderWindow &window, sf::RenderStates states)
{
	m_window.setView(m_worldView);
	m_worldGraph.renderState(window, states);

	if(Debug::isDebuggingEnabled() && Debug::isFpsVisible())
	{
		sf::View currentView = window.getView();
		sf::Vector2f viewCenter = currentView.getCenter();
		sf::Vector2f viewSize = currentView.getSize();
		sf::Vector2f topLeftPosition = sf::Vector2f(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);
		m_fpsText.setPosition(topLeftPosition);
		window.draw(m_fpsText, states);
	}
}



