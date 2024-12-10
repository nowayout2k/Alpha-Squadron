//
// Created by Johnnie Otis on 6/11/24.
//

#ifndef DEBUG_H_
#define DEBUG_H_

#define DEBUGGING_ENABLED true
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>
#include <iostream>
#include <string>

class World;

class Debug
{
 public:
	static void init();
	static void toggleFps();
	static void update(float deltaTime);
	static void render(sf::RenderWindow &window, sf::RenderStates& states);
	static void log(const std::string& message);
	template<typename... Args>
	static void log(Args... args)
	{
#if DEBUGGING_ENABLED
		std::ostringstream oss;
		((oss << args << " "), ...);
		std::string output = oss.str();
		if (!output.empty() && output.back() == ' ')
			output.pop_back();
		std::cout << "LOG: " << output << std::endl;
#endif
	}
	static void logWarning(const std::string& message);
	static void logError(const std::string& message);
 private:
#if DEBUGGING_ENABLED
	static bool m_fpsVisible;
	static sf::Text m_fpsText;
	static float m_timeSinceLastFpsUpdate;
	static int m_framesSinceLastFpsUpdate;
#endif
};

#endif //DEBUG_H_
