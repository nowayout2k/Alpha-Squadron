//
// Created by Johnnie Otis on 6/13/24.
//

#ifndef ENGINE_H_
#define ENGINE_H_

#include "World.h"
#include "Player.h"
#include "StateStack.h"

class Engine
{
 public:
	Engine();
	void update(float deltaTime);
	void render();
	void processEvents();
	void run();
	void registerStates();
 private:
	void createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
	bool m_isPaused;
	sf::RenderWindow m_window;
	Player m_input;
	StateStack m_stateStack;
};

#endif //ENGINE_H_
