//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/WindowManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow WindowManager::m_currentWindow;

sf::RenderWindow& WindowManager::createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style) // NOLINT(*-convert-member-functions-to-static)
{
	m_currentWindow.create(mode, title, style);
	m_currentWindow.setFramerateLimit(60);
	m_currentWindow.setPosition(sf::Vector2i(0,0));
	m_currentWindow.setMouseCursorVisible(false);
	m_currentWindow.setVerticalSyncEnabled(true);
	m_currentWindow.setActive(true);
	return m_currentWindow;
}
