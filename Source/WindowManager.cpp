//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/WindowManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow WindowManager::currentWindow;

sf::RenderWindow& WindowManager::CreateWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style) // NOLINT(*-convert-member-functions-to-static)
{
	currentWindow.create(mode, title, style);
	currentWindow.setFramerateLimit(60);
	currentWindow.setPosition(sf::Vector2i(0,0));
	currentWindow.setMouseCursorVisible(false);
	currentWindow.setVerticalSyncEnabled(true);
	currentWindow.setActive(true);
	return currentWindow;
}
