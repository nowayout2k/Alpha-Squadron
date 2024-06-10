//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/WindowHandler.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow WindowHandler::m_window;

sf::RenderWindow& WindowHandler::createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style) // NOLINT(*-convert-member-functions-to-static)
{
	m_window.create(mode, title, style);
	m_window.setFramerateLimit(120);
	m_window.setPosition(sf::Vector2i(0,0));
	m_window.setMouseCursorVisible(false);
	m_window.setVerticalSyncEnabled(false);
	m_window.setActive(true);
	return m_window;
}
