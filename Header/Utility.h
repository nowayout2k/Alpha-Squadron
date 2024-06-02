//
// Created by Johnnie on 5/27/2024.
//

#ifndef SFML_CORE_HEADER_UTILITY_H_
#define SFML_CORE_HEADER_UTILITY_H_
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
    static void BeginStopwatch(std::string message);
    static void EndStopwatch(std::string message);
    template<typename T> static std::string GetHash(const T& obj);
private:
    static sf::Clock clock;
};
#endif //SFML_CORE_HEADER_UTILITY_H_
