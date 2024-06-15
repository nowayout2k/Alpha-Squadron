//
// Created by Johnnie Otis on 6/11/24.
//

#include "../Header/Debug.h"

#if DEBUGGING_ENABLED
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

bool Debug::m_fpsVisible = false;
sf::Text Debug::m_fpsText;
float Debug::m_timeSinceLastFpsUpdate = 0;
int Debug::m_framesSinceLastFpsUpdate = 0;
#endif

void Debug::init()
{
#if DEBUGGING_ENABLED
	m_fpsText.setFont(*DataCache::getFont(FontType::Gamer));
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

	if(m_timeSinceLastFpsUpdate > 1)
	{
		m_fpsText.setString(std::to_string((int)(m_framesSinceLastFpsUpdate/m_timeSinceLastFpsUpdate)));
		m_timeSinceLastFpsUpdate = 0;
		m_framesSinceLastFpsUpdate = 0;
	}
#endif
}

void Debug::log(LogType logType, const std::string& message)
{
#if DEBUGGING_ENABLED
	switch (logType)
	{
	case Error:
		std::cout << "ERROR: " << message << std::endl;
		break;
	case Verbose:
		std::cout << "LOG: " << message << std::endl;
		break;
	case Warning:
		std::cout << "WARNING: " << message << std::endl;
		break;
	case Test:
		std::cout << "TEST: " << message << std::endl;
		break;
	}
#endif
}

void Debug::render(sf::RenderWindow& window, sf::RenderStates states)
{
#if DEBUGGING_ENABLED
	if(m_fpsVisible)
		window.draw(m_fpsText);
#endif
}
