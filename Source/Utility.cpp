//
// Created by Johnnie on 5/27/2024.
//

#include <SFML/System.hpp>
#include <iostream>
#include "../Header/Utility.h"

void Utility::Timer()
{
	sf::Clock clock;
	sf::Time elapsed = clock.getElapsedTime();
	std::cout << "Elapsed time: " << elapsed.asSeconds() << " seconds" << std::endl;

	// Vector example
	sf::Vector2f vec1(10.f, 5.f);
	sf::Vector2f vec2(2.f, 3.f);
	sf::Vector2f result = vec1 + vec2;
	std::cout << "Vector addition result: (" << result.x << ", " << result.y << ")" << std::endl;
}
