//
// Created by Johnnie Otis on 6/11/24.
//

#ifndef ALPHA_SQUADRON_HEADER_DEBUG_H_
#define ALPHA_SQUADRON_HEADER_DEBUG_H_

#include <string>
#include <SFML/Graphics/Text.hpp>
#include "TextEntity.h"

class Debug
{
 public:
	static void init();
	static void toggleFps() { m_fpsVisible = !m_fpsVisible; }
	static void update(float deltaTime);
	static void render(sf::RenderWindow &window);
 private:
	static bool m_fpsVisible;
	static sf::Text m_fpsText;
	static float m_timeSinceLastFpsUpdate;
	static int m_framesSinceLastFpsUpdate;
};

#endif //ALPHA_SQUADRON_HEADER_DEBUG_H_
