//
// Created by Johnnie Otis on 5/30/24.
//

#include "World.h"
#include "../Game/Tomcat.h"
#include "Audio.h"
#include "GameText.h"

World::World(sf::RenderWindow& window) : m_window(window), m_worldView(window.getDefaultView()),
			m_worldBounds(0.0f,0.0f,10000.0f,m_worldView.getSize().y),
			m_spawnPosition(0, m_worldView.getSize().y/2),
			m_playerAircraft(nullptr), m_scrollSpeed(50.0f), m_viewPositionOffset(0,0), m_commandQueue()
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

	std::unique_ptr<Aircraft> player(new Tomcat(NodeType::Player));
	m_playerAircraft = player.get();
	m_playerAircraft->setPosition(m_spawnPosition);
	m_playerAircraft->setVelocity(m_scrollSpeed, 0);
	m_playerAircraft->setScale(4.0, 4.0);
	m_worldLayers[static_cast<int>(Layer::Collision)]->attachNode(std::move(player));

	Audio::playMusic(MusicId::UNSquadronLevel1, 10);
}

void World::loadResources()
{
	m_worldGraph.loadStateResources();
}

void World::update(float deltaTime)
{
	m_worldView.move(m_scrollSpeed * deltaTime, 0.f);
	m_playerAircraft->setVelocity(0,0);

	while (!m_commandQueue.isEmpty())
		m_worldGraph.onCommand(m_commandQueue.pop(), deltaTime);

	sf::Vector2f velocity = m_playerAircraft->getVelocity();
	if (velocity.x != 0.f && velocity.y != 0.f)
		m_playerAircraft->setVelocity(velocity / std::sqrt(2.f));

	m_playerAircraft->accelerate(m_scrollSpeed, 0.f);

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



