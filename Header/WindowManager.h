//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef ALPHA_SQUADRON_HEADER_WINDOWMANAGER_H_
#define ALPHA_SQUADRON_HEADER_WINDOWMANAGER_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

static class WindowManager
{
public:
	static sf::RenderWindow& createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
    static sf::Vector2u getSize() { return m_currentWindow.getSize(); };
 private:
	static sf::RenderWindow m_currentWindow;
};


#endif //ALPHA_SQUADRON_HEADER_WINDOWMANAGER_H_
