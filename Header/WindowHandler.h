//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef ALPHA_SQUADRON_HEADER_WINDOWHANDLER_H_
#define ALPHA_SQUADRON_HEADER_WINDOWHANDLER_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class WindowHandler
{
public:
	static sf::RenderWindow& createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
    static sf::Vector2u getSize() { return m_window.getSize(); };
 private:
	static sf::RenderWindow m_window;
};


#endif //ALPHA_SQUADRON_HEADER_WINDOWHANDLER_H_
