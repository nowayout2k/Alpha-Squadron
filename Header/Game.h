//
// Created by Johnnie Otis on 6/13/24.
//

#ifndef GAME_H_
#define GAME_H_

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

#endif //GAME_H_
