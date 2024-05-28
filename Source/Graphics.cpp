//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Graphics.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::RenderWindow& Graphics::CreateWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style)
{
	currentWindow.create(mode, title, style);
	currentWindow.setFramerateLimit(60);//: Sets the maximum frame rate of the window.
	currentWindow.setPosition(sf::Vector2i(0,0));//: Sets the position of the window on the screen.
	currentWindow.setMouseCursorVisible(false);//: Sets the visibility of the mouse cursor in the window.
	currentWindow.setVerticalSyncEnabled(true);//: Enables or disables vertical synchronization.
	currentWindow.setActive(true);
	return currentWindow;
}
