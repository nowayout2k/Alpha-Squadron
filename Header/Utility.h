//
// Created by Johnnie on 5/27/2024.
//

#ifndef SFML_CORE_HEADER_UTILITY_H_
#define SFML_CORE_HEADER_UTILITY_H_

namespace SfmlCoreUtility
{
	class Utility
	{
		/*Time Functions:

			sf::Clock::restart: Restarts the clock and returns the elapsed time.
		sf::Clock::getElapsedTime: Returns the elapsed time since the clock was last restarted.
		sf::Time::asSeconds: Converts a time value to seconds.
		sf::Time::asMilliseconds: Converts a time value to milliseconds.
		sf::sleep: Suspends the execution of the current thread for a specified duration.
		Window Functions:

			sf::VideoMode::getDesktopMode: Returns the desktop video mode.
		sf::VideoMode::getFullscreenModes: Returns a list of all supported fullscreen modes.
		sf::Mouse::getPosition: Returns the current global position of the mouse cursor.
		sf::Mouse::setPosition: Sets the current global position of the mouse cursor.
		sf::Joystick::isConnected: Checks if a joystick is connected.
		sf::Joystick::getAxisPosition: Returns the current position of a joystick axis.
		sf::Clipboard::setString: Sets the content of the system clipboard to a string.
		sf::Clipboard::getString: Retrieves the content of the system clipboard as a string.
		File System Functions:

			sf::FileInputStream: Provides input stream functionality for reading from files.
		sf::FileOutputStream: Provides output stream functionality for writing to files.
		sf::File::open: Opens a file for reading or writing.
		sf::File::close: Closes a previously opened file.
		sf::File::getSize: Returns the size of a file in bytes.
		Utility Functions:

			sf::IpAddress::getLocalAddress: Returns the local machine's IP address.
		sf::IpAddress::getPublicAddress: Returns the public IP address of the machine.
		sf::IpAddress::resolve: Resolves a host name to an IP address.
		sf::String: Represents a string of UTF-32 characters.
		sf::Clock: Measures time intervals with high precision.
		Threading Functions:

			sf::Thread::launch: Creates and launches a new thread.
		sf::Thread::wait: Waits for a thread to finish executing.*/
		static void Timer();
	};
}
#endif //SFML_CORE_HEADER_UTILITY_H_
