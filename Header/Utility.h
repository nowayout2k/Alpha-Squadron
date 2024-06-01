//
// Created by Johnnie on 5/27/2024.
//

#ifndef SFML_CORE_HEADER_UTILITY_H_
#define SFML_CORE_HEADER_UTILITY_H_

namespace SfmlCoreUtility
{
	class Utility
	{
		/*
		sf::Clock::restart: Restarts the clock and returns the elapsed time.
		sf::Clock::getElapsedTime: Returns the elapsed time since the clock was last restarted.
		sf::Time::asSeconds: Converts a time value to seconds.
		sf::Time::asMilliseconds: Converts a time value to milliseconds.
		sf::sleep: Suspends the execution of the current thread for a specified duration.
 		sf::FileInputStream: Provides input stream functionality for reading from files.
		sf::FileOutputStream: Provides output stream functionality for writing to files.
		sf::File::open: Opens a file for reading or writing.
		sf::File::close: Closes a previously opened file.
		sf::File::getSize: Returns the size of a file in bytes.
		sf::Clock: Measures time intervals with high precision.
		sf::Thread::launch: Creates and launches a new thread.
		sf::Thread::wait: Waits for a thread to finish executing.
		 */
		static void Timer();
        template<typename T> static std::string GetHash(const T& obj);
	};
}
#endif //SFML_CORE_HEADER_UTILITY_H_
