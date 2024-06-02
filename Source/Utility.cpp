//
// Created by Johnnie on 5/27/2024.
//

#include <SFML/System.hpp>
#include <iostream>
#include "../Header/Utility.h"
#include "../Header/Logger.h"

sf::Clock Utility::clock;

void Utility::BeginStopwatch(std::string message)
{
    clock.restart();
    sf::Time elapsed = clock.getElapsedTime();
    Logger::Log(LogType::Test, message + " Stopwatch Started!");
}

void Utility::EndStopwatch(std::string message)
{
    sf::Time elapsed = clock.getElapsedTime();
    Logger::Log(LogType::Test, message + " Stopwatch stopped at: " + std::to_string(elapsed.asSeconds()) + " seconds");
}

template<typename T>
std::string Utility::GetHash(const T& obj)
{
    // Serialize the object into a string
    std::string data(reinterpret_cast<const char*>(&obj), sizeof(obj));

    // Use a hash function (e.g., std::hash) to generate a hash of the serialized data
    std::hash<std::string> hasher;
    size_t hashValue = hasher(data);

    // Convert hash value to a string
    return std::to_string(hashValue);
}