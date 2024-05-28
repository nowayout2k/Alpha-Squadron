//
// Created by Johnnie on 5/27/2024.
//

#include <SFML/System.hpp>
#include <iostream>
#include "../Header/Utility.h"
#include "../Header/Logger.h"
namespace SfmlCoreUtility
{
	void Utility::Timer()
	{
		sf::Clock clock;
		sf::Time elapsed = clock.getElapsedTime();
		Logger::Log(LogType::Verbose, "Elapsed time: " + std::to_string(elapsed.asSeconds()) + " seconds");

		// Vector example
		sf::Vector2f vec1(10.f, 5.f);
		sf::Vector2f vec2(2.f, 3.f);
		sf::Vector2f result = vec1 + vec2;
		Logger::Log(LogType::Verbose,
			"Vector addition result: (" + std::to_string(result.x) + ", " + std::to_string(result.y) + ")");
	}
}