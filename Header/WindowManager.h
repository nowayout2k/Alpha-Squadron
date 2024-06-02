//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef SFML_CORE_HEADER_GRAPHICS_H_
#define SFML_CORE_HEADER_GRAPHICS_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

static class WindowManager
{
public:
	static sf::RenderWindow& CreateWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
    static sf::Vector2u GetSize() { return currentWindow.getSize(); };
 private:
	static sf::RenderWindow currentWindow;
};


#endif //SFML_CORE_HEADER_GRAPHICS_H_
