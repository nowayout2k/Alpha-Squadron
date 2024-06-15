//
// Created by Johnnie Otis on 6/13/24.
//

#include "../Header/Game.h"

sf::RenderWindow Game::m_window;

sf::RenderWindow& Game::createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style) // NOLINT(*-convert-member-functions-to-static)
{
	m_window.create(mode, title, style);
	m_window.setFramerateLimit(120);
	m_window.setPosition(sf::Vector2i(0,0));
	m_window.setMouseCursorVisible(false);
	m_window.setVerticalSyncEnabled(false);
	m_window.setActive(true);
	return m_window;
}