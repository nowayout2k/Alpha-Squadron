//
// Created by Johnnie Otis on 6/11/24.
//

#ifndef DEBUG_H_
#define DEBUG_H_

#define DEBUGGING_ENABLED true
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class World;

class Debug
{
 public:
	static void init(World* world);
	static void toggleFps();
	static void update(float deltaTime);
	static void render(sf::RenderWindow &window, sf::RenderStates states);
	static void log(const std::string& message);
	static void logWarning(const std::string& message);
	static void logError(std::exception exception);
 private:
	static World* m_world;
#if DEBUGGING_ENABLED
	static bool m_fpsVisible;
	static sf::Text m_fpsText;
	static float m_timeSinceLastFpsUpdate;
	static int m_framesSinceLastFpsUpdate;
#endif
};

#endif //DEBUG_H_
