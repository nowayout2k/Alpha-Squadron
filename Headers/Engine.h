// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ENGINE_H_
#define ENGINE_H_

#include "World.h"
#include "Player.h"
#include "StateStack.h"

class Engine
{
 public:
	Engine();
	void update(sf::Time deltaTime);
	void render();
	void processEvents();
	void run();
	void registerStates();
 private:
	void createWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
	bool m_isPaused;
	sf::RenderWindow m_window;
	Audio m_audio;
	StateStack m_stateStack;
	KeyBinding m_keyBinding1;
	KeyBinding m_keyBinding2;
};

#endif //ENGINE_H_
