//
// Created by Johnnie on 5/27/2024.
//

#ifndef ALPHA_SQUADRON_HEADER_UTILITY_H_
#define ALPHA_SQUADRON_HEADER_UTILITY_H_
#include <SFML/System/Clock.hpp>
#include "Logger.h"
class Utility
{
public:
	static void beginStopwatch(std::string message)
	{
		m_clock.restart();
		sf::Time elapsed = m_clock.getElapsedTime();
		Logger::Log(LogType::Test, message + " Stopwatch Started!");
	}

	static void endStopwatch(std::string message)
	{
		sf::Time elapsed = m_clock.getElapsedTime();
		Logger::Log(LogType::Test, message + " Stopwatch stopped at: " + std::to_string(elapsed.asSeconds()) + " seconds");
	}

	static float lerp(float a, float b, float t)
	{
		t = std::clamp(t, 0.0f, 1.0f);
		return a + (b - a) * t;
	}
private:
    static sf::Clock m_clock;

	/*
sf::sleep: Suspends the execution of the current thread for a specified duration.
sf::FileInputStream: Provides input stream functionality for reading from files.
sf::FileOutputStream: Provides output stream functionality for writing to files.
sf::File::open: Opens a file for reading or writing.
sf::File::close: Closes a previously opened file.
sf::File::getSize: Returns the size of a file in bytes.
sf::Thread::launch: Creates and launches a new thread.
sf::Thread::wait: Waits for a thread to finish executing.
 */
};
#endif //ALPHA_SQUADRON_HEADER_UTILITY_H_
