// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef DEBUG_H_
#define DEBUG_H_

#include <sstream>
#include <iostream>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class World; // Forward declaration of World

/**
 * @file Debug.h
 * @brief Declaration of the Debug utility class.
 *
 * The Debug class provides static functions for logging messages, warnings, and errors.
 * It also offers functionality to toggle FPS and collider visualization, and to check
 * if debugging is enabled.
 */
class Debug
{
 public:
	/**
	 * @brief Logs a series of arguments if debugging is enabled.
	 *
	 * The arguments are concatenated into a single string and printed to the console.
	 *
	 * @tparam Args Types of the arguments.
	 * @param args The arguments to log.
	 */
	template<typename... Args>
	static void log(Args... args)
	{
		if (!m_isDebuggingEnabled)
			return;

		std::ostringstream oss;
		((oss << args << " "), ...);
		std::string output = oss.str();
		if (!output.empty() && output.back() == ' ')
			output.pop_back();
		std::cout << "LOG: " << output << std::endl;
	}

	/**
	 * @brief Logs an error message if debugging is enabled.
	 *
	 * @param message The error message.
	 */
	static void logError(const std::string& message)
	{
		if (!m_isDebuggingEnabled)
			return;

		std::cout << "***** ERROR! " << message << " *****" << std::endl;
	}

	/**
	 * @brief Logs a warning message if debugging is enabled.
	 *
	 * @param message The warning message.
	 */
	static void logWarning(const std::string& message)
	{
		if (!m_isDebuggingEnabled)
			return;

		std::cout << "----- WARNING: " << message << " -----" << std::endl;
	}

	/**
	 * @brief Toggles the visibility of the FPS counter.
	 */
	static void toggleFps() { m_fpsVisible = !m_fpsVisible; }

	/**
	 * @brief Toggles the visibility of the colliders.
	 */
	static void toggleDrawColliders() { m_collidersVisible = !m_collidersVisible; }

	/**
	 * @brief Checks whether debugging is enabled.
	 *
	 * @return True if debugging is enabled; otherwise false.
	 */
	static bool isDebuggingEnabled() { return m_isDebuggingEnabled; }

	/**
	 * @brief Checks whether the FPS counter is visible.
	 *
	 * @return True if the FPS counter is visible; otherwise false.
	 */
	static bool isFpsVisible() { return m_fpsVisible; }

	/**
	 * @brief Checks whether colliders are visible.
	 *
	 * @return True if colliders are visible; otherwise false.
	 */
	static bool isCollidersVisible() { return m_collidersVisible; }

 private:
	static bool m_fpsVisible;         // Flag indicating if FPS display is visible.
	static bool m_collidersVisible;   // Flag indicating if collider visualization is enabled.
	static bool m_isDebuggingEnabled; // Flag indicating if debugging is enabled.
};

#endif // DEBUG_H_
