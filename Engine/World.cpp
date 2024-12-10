//
// Created by Johnnie Otis on 5/30/24.
//

#include "World.h"
#include "../Game/Tomcat.h"
#include "Audio.h"
#include "GameText.h"
#include "../Game/Chopper.h"
#include "Projectile.h"

float World::m_scrollSpeed = 500.0f;

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

void World::setup()
{
	for (int i = 0; i < static_cast<int>(Layer::LayerCount); ++i)
	{
		WorldNode::SmartNode layer(new EmptyWorldNode());
		m_worldLayers[i] = layer.get();
		m_worldGraph.attachNode(std::move(layer));
	}

	std::unique_ptr<GameSprite> backgroundSkySprite(
		new GameSprite(
			false,
			TextureId::SmoggySky,
			sf::IntRect(),
			sf::IntRect(0,0,m_worldBounds.width, m_worldView.getSize().y),
			true));
	backgroundSkySprite->setPosition(m_worldBounds.left,m_worldBounds.top);
	m_worldLayers[static_cast<int>(Layer::Background)]->attachNode(std::move(backgroundSkySprite));

	std::unique_ptr<GameSprite> backgroundBuildingsSprite(
		new GameSprite(
			false,
			TextureId::DecayedBuildings1,
			sf::IntRect(),
			sf::IntRect(0,0,m_worldBounds.width,m_worldView.getSize().y),
			true));
	backgroundBuildingsSprite->setPosition(m_worldBounds.left,m_worldBounds.top);
	m_worldLayers[static_cast<int>(Layer::Background)]->attachNode(std::move(backgroundBuildingsSprite));

	std::unique_ptr<Aircraft> player = createAircraft(AircraftType::Tomcat, m_spawnPosition, NodeType::Player, sf::Vector2f(4.0, 4.0));
	m_playerAircraft = player.get();
	m_playerAircraft->setVelocity(m_scrollSpeed, 0);
	m_worldLayers[static_cast<int>(Layer::Collision)]->attachNode(std::move(player));

	addEnemies();

	Audio::playMusic(MusicId::UNSquadronLevel1, 10);
}

void World::addEnemies()
{
	m_enemySpawnPoints.push_back(SpawnPoint(AircraftType::Tomcat, 5500.f));
	m_enemySpawnPoints.push_back(SpawnPoint(AircraftType::Chopper, 9000.f));

	std::sort(m_enemySpawnPoints.begin(), m_enemySpawnPoints.end(),
		[] (SpawnPoint lhs, SpawnPoint rhs)
		{
		  return lhs.spawnDistance > rhs.spawnDistance;
		});
}

void World::guideMissiles()
{
	Command enemyCollector;
	enemyCollector.nodeType &= (int)NodeType::Enemy;
	enemyCollector.action = derivedAction<Aircraft>([this] (Aircraft& enemy, float dt)
		{
		  if (!enemy.isDestroyPending())
			  m_activeEnemies.push_back(&enemy);
		});
	Command missileGuider;
	missileGuider.nodeType &= (int)NodeType::Projectile;
	missileGuider.action = derivedAction<Projectile>(
		[this] (Projectile& missile, float dt)
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
			  missile.guideTowards(
				  closestEnemy->getWorldPosition());
		});
	m_commandQueue.push(enemyCollector);
	m_commandQueue.push(missileGuider);
	m_activeEnemies.clear();
}

void World::spawnEnemies()
{
	auto bounds = getBattlefieldBounds();

	while (!m_enemySpawnPoints.empty() && m_enemySpawnPoints.back().spawnDistance < bounds.left + bounds.width)
	{
		SpawnPoint spawn = m_enemySpawnPoints.back();
		auto enemy = createAircraft(spawn.type, sf::Vector2f(spawn.spawnDistance,0), NodeType::Enemy, sf::Vector2f(-4.0, 4.0));
		enemy->loadHierarchyResources();
		m_worldLayers[static_cast<int>(Layer::Collision)]->attachNode(std::move(enemy));
		m_enemySpawnPoints.pop_back();
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
	float scrollSpeedFactor = 1;
	m_playerAircraft->setVelocity(0,0);

	while (!m_commandQueue.isEmpty())
		m_worldGraph.onCommand(m_commandQueue.pop(), deltaTime);

	sf::Vector2f velocity = m_playerAircraft->getVelocity();
	if (velocity.x != 0.f && velocity.y != 0.f)
		m_playerAircraft->setVelocity(velocity / std::sqrt(2.f));

	sf::Vector2f viewCenter = m_worldView.getCenter();
	sf::Vector2f viewSize = m_worldView.getSize();
	sf::Vector2f currentViewPosRight = sf::Vector2f(viewCenter.x + viewSize.x / 2, viewCenter.y + viewSize.y / 2);

/*	if(currentViewPosRight.x > m_worldBounds.width * .75f)
	{
		float distanceToEnd = m_worldBounds.width - currentViewPosRight.x;
		float totalSlowDownDistance = m_worldBounds.width - (m_worldBounds.width * .75f);
		scrollSpeedFactor = distanceToEnd / totalSlowDownDistance;
		if(scrollSpeedFactor < .2f)
			scrollSpeedFactor = .2f;
	}*/

	//if(currentViewPosRight.x < m_worldBounds.width)
	//{
		m_worldView.move(m_scrollSpeed * scrollSpeedFactor * deltaTime, 0.f);
		m_playerAircraft->accelerate(m_scrollSpeed * scrollSpeedFactor, 0.f);
		spawnEnemies();
	//}

	m_worldGraph.updateHierarchy(deltaTime, m_commandQueue);

	sf::FloatRect viewBounds(m_worldView.getCenter() - m_worldView.getSize() / 2.f,m_worldView.getSize());
	const auto spriteBounds = m_playerAircraft->getGlobalBounds();
	sf::Vector2f position = m_playerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + 0);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - spriteBounds.width);
	position.y = std::max(position.y, viewBounds.top + 0);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - spriteBounds.height);
	m_playerAircraft->setPosition(position);

	handleCollisions();
}

void World::render(sf::RenderWindow &window, sf::RenderStates states)
{
	m_window.setView(m_worldView);
	m_worldGraph.renderState(window, states);
}

void World::handleCollisions()
{
    /*for (const auto& entity : m_entities)
    {
		if(entity->isDestroyPending())
			continue;

        for (const auto& other : m_entities)
        {
            if(other->isDestroyPending() || entity == other)
                continue;

            if(entity && entity->hasCollision() && other && other->hasCollision() &&
				entity->isColliding(other->getGlobalBounds()))
            {
				entity->collision(other.get());
            }
        }
    }*/
}



