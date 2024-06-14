//
// Created by Johnnie Otis on 6/11/24.
//
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Header/Debug.h"

bool Debug::m_fpsVisible = false;
sf::Text Debug::m_fpsText;
float Debug::m_timeSinceLastFpsUpdate = 0;
int Debug::m_framesSinceLastFpsUpdate = 0;

void Debug::init()
{
	m_fpsText.setFont(*DataCache::getFont(Font::Gamer));
	m_fpsText.setPosition(sf::Vector2f());
	m_fpsText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_fpsText.setCharacterSize(100);
	m_fpsText.setFillColor(sf::Color::White);
	m_fpsText.setString("0000");
}

void Debug::update(float deltaTime)
{
	m_framesSinceLastFpsUpdate++;
	m_timeSinceLastFpsUpdate += deltaTime;

	if(m_timeSinceLastFpsUpdate > 5)
	{
		m_fpsText.setString(std::to_string(m_framesSinceLastFpsUpdate/m_timeSinceLastFpsUpdate));
		m_timeSinceLastFpsUpdate = 0;
		m_framesSinceLastFpsUpdate = 0;
	}
}

void Debug::render(sf::RenderWindow& window)
{
	if(m_fpsVisible)
		window.draw(m_fpsText);
}