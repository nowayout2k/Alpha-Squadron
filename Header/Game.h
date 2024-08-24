//
// Created by Johnnie Otis on 6/13/24.
//

#ifndef GAME_H_
#define GAME_H_

#include "World.h"
#include "Player.h"

class Game
{
 public:
	Game();
	void update(float deltaTime);
	void render();
	void processInput();
	void run();
 private:
	void createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
	bool m_isPaused;
	sf::RenderWindow m_window;
	std::unique_ptr<World> m_world;
	Player m_player;
};

#endif //GAME_H_
