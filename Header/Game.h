//
// Created by Johnnie Otis on 6/13/24.
//

#ifndef ALPHA_SQUADRON_HEADER_GAME_H_
#define ALPHA_SQUADRON_HEADER_GAME_H_
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Scene.h"

class Game
{
 public:
	Game() {};
	void createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
	static sf::Vector2u getWindowSize() { return m_window.getSize(); };
	int getScreenSection() { return 1; };
	void update(float deltaTime);
	void render(sf::RenderWindow &window, sf::RenderStates states);
	void processEvents();
	void run();

 private:
	static sf::RenderWindow m_window;
	Scene m_scene;
};

#endif //ALPHA_SQUADRON_HEADER_GAME_H_
