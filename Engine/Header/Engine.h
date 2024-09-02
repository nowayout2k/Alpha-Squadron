//
// Created by Johnnie Otis on 6/13/24.
//

#ifndef ENGINE_H_
#define ENGINE_H_

#include "World.h"
#include "Input.h"

class Engine
{
 public:
	Engine();
	void update(float deltaTime);
	void render();
	void processInput();
	void run();
 private:
	void createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
	bool m_isPaused;
	sf::RenderWindow m_window;
	std::unique_ptr<World> m_world;
	Input m_player;
};

#endif //ENGINE_H_
