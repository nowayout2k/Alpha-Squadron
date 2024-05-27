#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Header/Input.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Graphics Example");
    Input input;
    sf::CircleShape circleShape(55);
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
