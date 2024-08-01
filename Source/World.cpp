//
// Created by Johnnie Otis on 5/30/24.
//

#include "../Header/World.h"
#include "../Header/Tomcat.h"
#include "../Header/Audio.h"
#include "../Header/GameText.h"

World::World(sf::RenderWindow& window) : m_window(window), m_worldView(window.getDefaultView()),
			m_worldBounds(0.0f,0.0f,10000.0f,m_worldView.getSize().y),
			m_spawnPosition(0, m_worldView.getSize().y/2),
			m_playerAircraft(nullptr), m_scrollSpeed(50.0f), m_viewPositionOffset(0,0)
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
	for (int i = 0; i < LayerCount; ++i)
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
	m_worldLayers[Background]->attachNode(std::move(backgroundSkySprite));

	std::unique_ptr<GameSprite> backgroundBuildingsSprite(
		new GameSprite(
			false,
			TextureId::DecayedBuildings1,
			sf::IntRect(),
			sf::IntRect(0,0,m_worldBounds.width,m_worldView.getSize().y),
			true));
	backgroundBuildingsSprite->setPosition(m_worldBounds.left,m_worldBounds.top);
	m_worldLayers[Background]->attachNode(std::move(backgroundBuildingsSprite));

	std::unique_ptr<Aircraft> player(new Tomcat());
	m_playerAircraft = player.get();
	m_playerAircraft->setPosition(m_spawnPosition);
	m_playerAircraft->setVelocity(m_scrollSpeed, 0);
	m_playerAircraft->setScale(4.0, 4.0);
	m_worldLayers[Collision]->attachNode(std::move(player));

	Audio::playMusic(MusicId::UNSquadronLevel1, 10);
}

void World::loadResources()
{
	m_worldGraph.loadStateResources();
}

void World::update(float deltaTime)
{
	m_worldGraph.updateState(deltaTime);

	sf::Vector2f velocity(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		velocity.y -= 800.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		velocity.y += 800.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		velocity.x -= 800.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		velocity.x += 800.f;

	if (velocity.x != 0.f && velocity.y != 0.f)
	{
		velocity.x /= std::sqrt(2.f);
		velocity.y /= std::sqrt(2.f);
	}

	m_playerAircraft->setVelocity(velocity);

	sf::Vector2f position = m_playerAircraft->getPosition();

	if (position.x <= m_viewPositionOffset.x)
	{
		position = sf::Vector2f(m_viewPositionOffset.x, position.y);
	}
	else if (position.x > m_viewPositionOffset.x + m_worldView.getSize().x - m_playerAircraft->getGlobalBounds().width)
	{
		position = sf::Vector2f(m_viewPositionOffset.x + m_worldView.getSize().x - m_playerAircraft->getGlobalBounds().width, position.y);
	}

	if (position.y <= 0)
	{
		position = sf::Vector2f(position.x, 0);
	}
	else if (position.y > 0 + m_worldView.getSize().y - m_playerAircraft->getGlobalBounds().height)
	{
		position = sf::Vector2f(position.x, 0 + m_worldView.getSize().y - m_playerAircraft->getGlobalBounds().height);
	}

	m_playerAircraft->setPosition(position);

	if(m_viewPositionOffset.x < m_worldBounds.width - m_worldView.getSize().x)
	{
		auto viewMovementThisFrame = m_scrollSpeed * deltaTime;
		m_viewPositionOffset += sf::Vector2f(viewMovementThisFrame, 0);
		m_worldView.move(viewMovementThisFrame, 0.0f);
		if(m_playerAircraft->getVelocity().x == 0)
		{
			m_playerAircraft->setVelocity(m_scrollSpeed, m_playerAircraft->getVelocity().y);
		}
	}

	WorldNode::SmartNode pro = nullptr;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		pro = m_playerAircraft->fireBullet(sf::Vector2f(1000, 0));
	}

	if(pro != nullptr)
	{
		pro->setScale(4.0,4.0);
		pro->loadStateResources();
		m_worldLayers[Layer::Collision]->attachNode(std::move(pro));
	}

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


