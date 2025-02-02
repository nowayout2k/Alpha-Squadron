// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef DEBUG_H_
#define DEBUG_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>
#include <iostream>
#include <string>

class World;

class Debug
{
 public:
	template<typename... Args>
	static void log(Args... args)
	{
		if(!m_isDebuggingEnabled)
			return;

		std::ostringstream oss;
		((oss << args << " "), ...);
		std::string output = oss.str();
		if (!output.empty() && output.back() == ' ')
			output.pop_back();
		std::cout << "LOG: " << output << std::endl;
	}

	static void logError(const std::string& message)
	{
		if(!m_isDebuggingEnabled)
			return;

		std::cout << "***** ERROR! " << message << "*****" << std::endl;
	}

	static void logWarning(const std::string& message)
	{
		if(!m_isDebuggingEnabled)
			return;

		std::cout << "-----WARNING: " << message << "-----" << std::endl;
	}

	static void toggleFps() { m_fpsVisible = !m_fpsVisible; }
	static void toggleDrawColliders() { m_collidersVisible = !m_collidersVisible; }
	static bool isDebuggingEnabled() { return m_isDebuggingEnabled; }
	static bool isFpsVisible() { return m_fpsVisible; }
	static bool isCollidersVisible() { return m_collidersVisible; }
 private:
	static bool m_fpsVisible;
	static bool m_collidersVisible;
	static bool m_isDebuggingEnabled;
};

#endif //DEBUG_H_
