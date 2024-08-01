//
// Created by Johnnie Otis on 6/13/24.
//

#ifndef GAME_H_
#define GAME_H_

#include "World.h"

class Game
{
 public:
	Game();
	void update(float deltaTime);
	void render();
	void processEvents();
	void run();
 private:
	void createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
	bool m_isPaused;
	sf::RenderWindow m_window;
	std::unique_ptr<World> m_world;
};

#endif //GAME_H_
