//
// Created by Johnnie Otis on 6/11/24.
//

#include "Debug.h"
#include "GameText.h"
#include "Engine.h"
#include <iostream>
#include <string>

#if DEBUGGING_ENABLED
bool Debug::m_fpsVisible = false;
sf::Text Debug::m_fpsText;
float Debug::m_timeSinceLastFpsUpdate = 0;
int Debug::m_framesSinceLastFpsUpdate = 0;
#endif

void Debug::init()
{
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
	if(m_fpsVisible)
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
#endif
}

void Debug::logError(const std::string& message)
{
#if DEBUGGING_ENABLED
	std::cout << "***** ERROR! " << message << "*****" << std::endl;
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

void Debug::render(sf::RenderWindow& window, sf::RenderStates& states)
{
#if DEBUGGING_ENABLED
	if(m_fpsVisible)
	{
		sf::View currentView = window.getView();
		sf::Vector2f viewCenter = currentView.getCenter();
		sf::Vector2f viewSize = currentView.getSize();
		sf::Vector2f topLeftPosition = sf::Vector2f(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);
		m_fpsText.setPosition(topLeftPosition);
		window.draw(m_fpsText, states);
	}

#endif
}
void Debug::toggleFps()
{
#if DEBUGGING_ENABLED
	m_fpsVisible = !m_fpsVisible;
#endif
}
