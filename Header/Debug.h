//
// Created by Johnnie Otis on 6/11/24.
//

#ifndef ALPHA_SQUADRON_HEADER_DEBUG_H_
#define ALPHA_SQUADRON_HEADER_DEBUG_H_

#define DEBUGGING_ENABLED true

#include <string>
#include <SFML/Graphics/Text.hpp>
#include "GameText.h"
#include "LogType.h"

class Debug
{
 public:
	static void init();
	static void toggleFps()
	{
#if DEBUGGING_ENABLED
	m_fpsVisible = !m_fpsVisible;
#endif
	}
	static void update(float deltaTime);
	static void render(sf::RenderWindow &window, sf::RenderStates states);
	static void log(LogType logType, const std::string& message);
 private:
#if DEBUGGING_ENABLED
	static bool m_fpsVisible;
	static sf::Text m_fpsText;
	static float m_timeSinceLastFpsUpdate;
	static int m_framesSinceLastFpsUpdate;
#endif
};

#endif //ALPHA_SQUADRON_HEADER_DEBUG_H_
