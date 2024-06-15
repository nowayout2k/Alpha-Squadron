//
// Created by Johnnie Otis on 6/13/24.
//

#ifndef ALPHA_SQUADRON_HEADER_GAME_H_
#define ALPHA_SQUADRON_HEADER_GAME_H_
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Game
{
 public:
	static sf::RenderWindow& createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
	static sf::Vector2u getWindowSize() { return m_window.getSize(); };
	static int getScreenSection() { return 1; };

 private:
	static sf::RenderWindow m_window;
};

#endif //ALPHA_SQUADRON_HEADER_GAME_H_
