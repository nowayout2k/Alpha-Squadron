//
// Created by Johnnie on 5/27/2024.
//

#include <SFML/System.hpp>
#include <iostream>
#include "../Header/Utility.h"
#include "../Header/Logger.h"

sf::Clock Utility::m_clock;

void Utility::beginStopwatch(std::string message)
{
    m_clock.restart();
    sf::Time elapsed = m_clock.getElapsedTime();
    Logger::Log(LogType::Test, message + " Stopwatch Started!");
}

void Utility::endStopwatch(std::string message)
{
    sf::Time elapsed = m_clock.getElapsedTime();
    Logger::Log(LogType::Test, message + " Stopwatch stopped at: " + std::to_string(elapsed.asSeconds()) + " seconds");
}

float Utility::lerp(float a, float b, float t)
{
	t = std::clamp(t, 0.0f, 1.0f);
	return a + (b - a) * t;
}

template<typename T>
std::string Utility::getHash(const T& obj)
{
    // Serialize the object into a string
    std::string data(reinterpret_cast<const char*>(&obj), sizeof(obj));

    // Use a hash function (e.g., std::hash) to generate a hash of the serialized data
    std::hash<std::string> hasher;
    size_t hashValue = hasher(data);

    // Convert hash value to a string
    return std::to_string(hashValue);
}