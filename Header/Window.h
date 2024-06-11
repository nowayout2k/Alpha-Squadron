//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef ALPHA_SQUADRON_HEADER_WINDOW_H_
#define ALPHA_SQUADRON_HEADER_WINDOW_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Window
{
public:
	static sf::RenderWindow& createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
    static sf::Vector2u getSize() { return m_window.getSize(); };
	static std::string getFps() { return std::to_string(m_fps); };
	static void update(float deltaTime);
 private:
	static sf::RenderWindow m_window;
	static float m_timeElapsed;
	static int m_frameCount;
	static int m_fps;
};


#endif //ALPHA_SQUADRON_HEADER_WINDOW_H_
