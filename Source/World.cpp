//
// Created by Johnnie Otis on 5/30/24.
//

#include "../Header/World.h"
#include "../Header/EnemyAircraft.h"
#include "../Header/PlayerAircraft.h"
#include "../Header/Audio.h"
#include "../Header/GameText.h"

World::World(sf::RenderWindow& window) : m_window(window), m_worldView(window.getDefaultView()),
			m_worldBounds(0.0f,0.0f,2000.0f,m_worldView.getSize().y),
			m_spawnPosition(0, m_worldView.getSize().y/2),
			m_playerAircraft(nullptr), m_scrollSpeed(1.0f)
{
	setup();
	loadResources();
	//m_worldView.setCenter(m_spawnPosition);
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
	for (int i = 0; i < LayerCount; ++i)
	{
		WorldNode::SmartNode layer(new EmptyWorldNode());
		m_worldLayers[i] = layer.get();
		m_worldGraph.attachNode(std::move(layer));
	}

	std::unique_ptr<GameSprite> backgroundSprite(
		new GameSprite(EntityType::Background,
			false,
			TextureId::Coin,
			sf::IntRect(m_worldBounds),
			true));
	backgroundSprite->setPosition(m_worldBounds.left,m_worldBounds.top);
	m_worldLayers[Background]->attachNode(std::move(backgroundSprite));

	std::unique_ptr<Aircraft> player(new PlayerAircraft());
	m_playerAircraft = player.get();
	m_playerAircraft->setPosition(m_spawnPosition);
	//m_playerAircraft->setVelocity(m_scrollSpeed, 40.f);

	m_worldLayers[Collision]->attachNode(std::move(player));
	std::unique_ptr<WorldNode> enemy1(new EnemyAircraft(true,
		sf::Vector2f((float)m_worldBounds.getSize().x-500, (float)m_worldBounds.getSize().y+100)));
	m_worldLayers[Collision]->attachNode(std::move(enemy1));

	std::unique_ptr<WorldNode> enemy2(new EnemyAircraft(true,
		sf::Vector2f((float)m_worldBounds.getSize().x-500, (float)m_worldBounds.getSize().y+100)));
	m_worldLayers[Collision]->attachNode(std::move(enemy2));
	Audio::playMusic(MusicId::UNSquadronLevel1, 10);
}

void World::loadResources()
{
	m_worldGraph.loadStateResources();
}
float totalMovement = 0;
void World::update(float deltaTime)
{
	totalMovement += m_scrollSpeed * deltaTime;
	m_worldView.move(m_scrollSpeed * deltaTime, 0.0f);
	m_worldGraph.updateState(deltaTime);

	sf::Vector2f position = m_playerAircraft->getPosition();

	sf::Rect<float> bounds;
	bounds.left = totalMovement;
	bounds.top = 0;
	bounds.width = m_worldView.getSize().x;
	bounds.height = m_worldView.getSize().y;

	if (position.x <= bounds.left)
	{
		position = sf::Vector2f(bounds.left, position.y);
		m_playerAircraft->setPosition(position);
	}
	else if (position.x > bounds.left + bounds.width - m_playerAircraft->getScaledTextureSize().x)
	{
		position = sf::Vector2f(bounds.left + bounds.width - m_playerAircraft->getScaledTextureSize().x, position.y);
		m_playerAircraft->setPosition(position);
	}
	if (position.y <= bounds.top)
	{
		position = sf::Vector2f(position.x, bounds.top);
		m_playerAircraft->setPosition(position);
	}
	else if (position.y > bounds.top + bounds.height - m_playerAircraft->getScaledTextureSize().y)
	{
		position = sf::Vector2f(position.x, bounds.top + bounds.height - m_playerAircraft->getScaledTextureSize().y);
		m_playerAircraft->setPosition(position);
	}

	handleCollisions();
}

void World::render(sf::RenderWindow &window, sf::RenderStates states)
{
	window.setView(m_worldView);
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

