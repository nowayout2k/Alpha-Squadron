//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Window.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow Window::m_window;
float Window::m_timeElapsed = 0;
int Window::m_frameCount = 0;
int Window::m_fps = 0;

sf::RenderWindow& Window::createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style) // NOLINT(*-convert-member-functions-to-static)
{
	m_window.create(mode, title, style);
	m_window.setFramerateLimit(120);
	m_window.setPosition(sf::Vector2i(0,0));
	m_window.setMouseCursorVisible(false);
	m_window.setVerticalSyncEnabled(false);
	m_window.setActive(true);
	return m_window;
}

void Window::update(float deltaTime)
{
	m_frameCount++;
	m_timeElapsed += deltaTime;

	if(m_timeElapsed >= 1)
	{
		m_fps = m_frameCount/m_timeElapsed;
		m_frameCount = 0;
		m_timeElapsed = 0;
	}
}
