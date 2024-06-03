//
// Created by Johnnie on 5/27/2024.
//

#ifndef ALPHA_SQUADRON_HEADER_UTILITY_H_
#define ALPHA_SQUADRON_HEADER_UTILITY_H_
static class Utility
{
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
public:
    static void beginStopwatch(std::string message);
    static void endStopwatch(std::string message);
    template<typename T> static std::string getHash(const T& obj);
	static float lerp(float a, float b, float t);
private:
    static sf::Clock m_clock;
};
#endif //ALPHA_SQUADRON_HEADER_UTILITY_H_
