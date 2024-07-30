//
// Created by Johnnie Otis on 6/11/24.
//

#include "../Header/Debug.h"
#include "../Header/GameText.h"
#include <iostream>
#include <string>
#include "../Header/World.h"

#if DEBUGGING_ENABLED
bool Debug::m_fpsVisible = false;
sf::Text Debug::m_fpsText;
float Debug::m_timeSinceLastFpsUpdate = 0;
int Debug::m_framesSinceLastFpsUpdate = 0;
World* Debug::m_world = nullptr;
#endif

void Debug::init(World* world)
{
	m_world = world;
#if DEBUGGING_ENABLED
	m_fpsText.setFont(ResourceManager::loadResource(FontId::Gamer));
	m_fpsText.setPosition(sf::Vector2f());
	m_fpsText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_fpsText.setCharacterSize(100);
	m_fpsText.setFillColor(sf::Color::White);
	m_fpsText.setString("0000");
#endif
}

void Debug::update(float deltaTime)
{
#if DEBUGGING_ENABLED
	m_framesSinceLastFpsUpdate++;
	m_timeSinceLastFpsUpdate += deltaTime;
	auto view = m_world->m_worldView;
	if(m_fpsVisible && m_world)
	{
		m_fpsText.setPosition(m_world->m_viewPositionOffset);
	}
	if(m_timeSinceLastFpsUpdate > 1)
	{
		m_fpsText.setString(std::to_string((int)(m_framesSinceLastFpsUpdate/m_timeSinceLastFpsUpdate)));
		m_timeSinceLastFpsUpdate = 0;
		m_framesSinceLastFpsUpdate = 0;
	}
#endif
}

void Debug::logError(std::exception exception)
{
#if DEBUGGING_ENABLED
	std::cout << "***** ERROR! " << exception.what() << "*****" << std::endl;
	throw exception;
#endif
}

void Debug::log(const std::string& message)
{
#if DEBUGGING_ENABLED
	std::cout << "LOG: " << message << std::endl;
#endif
}

void Debug::logWarning(const std::string& message)
{
#if DEBUGGING_ENABLED
	std::cout << "-----WARNING: " << message << "-----" << std::endl;
#endif
}

void Debug::render(sf::RenderWindow& window, sf::RenderStates states)
{
#if DEBUGGING_ENABLED
	if(m_fpsVisible)
		window.draw(m_fpsText);
#endif
}
void Debug::toggleFps()
{
#if DEBUGGING_ENABLED
	m_fpsVisible = !m_fpsVisible;
#endif
}
