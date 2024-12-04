//
// Created by Johnnie Otis on 5/30/24.
//

#include "World.h"
#include "../Game/Tomcat.h"
#include "Audio.h"
#include "GameText.h"
#include "../Game/Chopper.h"

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

	std::unique_ptr<Aircraft> player(new Tomcat(NodeType::Player, sf::Vector2f(4.0, 4.0)));
	m_playerAircraft = player.get();
	m_playerAircraft->setPosition(m_spawnPosition);
	m_playerAircraft->setVelocity(m_scrollSpeed, 0);
	m_worldLayers[static_cast<int>(Layer::Collision)]->attachNode(std::move(player));

	std::unique_ptr<Aircraft> enemy(new Chopper(true, sf::Vector2f(m_worldView.getSize().x-100, 0), NodeType::Enemy, sf::Vector2f(-4.0, 4.0)));
	m_worldLayers[static_cast<int>(Layer::Collision)]->attachNode(std::move(enemy));

	std::unique_ptr<Aircraft> enemy2(new Tomcat(NodeType::Enemy, sf::Vector2f(-4.0, 4.0)));
	enemy2->setPosition(sf::Vector2f(m_worldView.getSize().x-200, m_worldView.getSize().y));
	m_worldLayers[static_cast<int>(Layer::Collision)]->attachNode(std::move(enemy2));

	Audio::playMusic(MusicId::UNSquadronLevel1, 10);
}

void World::loadResources()
{
	m_worldGraph.loadStateResources();
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

	if(currentViewPosRight.x < m_worldBounds.width)
	{
		m_worldView.move(m_scrollSpeed * scrollSpeedFactor * deltaTime, 0.f);
		m_playerAircraft->accelerate(m_scrollSpeed * scrollSpeedFactor, 0.f);
	}

	m_worldGraph.updateState(deltaTime);

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



