#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Header/Input.h"

int main()
{
    sf::Clock clock;
    sf::Time elapsed = clock.getElapsedTime();
    std::cout << "Elapsed time: " << elapsed.asSeconds() << " seconds" << std::endl;

    // Vector example
    sf::Vector2f vec1(10.f, 5.f);
    sf::Vector2f vec2(2.f, 3.f);
    sf::Vector2f result = vec1 + vec2;
    std::cout << "Vector addition result: (" << result.x << ", " << result.y << ")" << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Graphics Example");
    Input input;
    sf::CircleShape circleShape(5);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        input.HandleInput();
        window.draw(circleShape);
        window.display();
    }
    return 0;
}
