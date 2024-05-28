#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Header/Input.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Graphics Example");
    SfmlCoreInput::Input input;

	window.setFramerateLimit(60);//: Sets the maximum frame rate of the window.
	window.setTitle("SFML Core");//: Sets the title of the window.
	window.setSize(sf::Vector2u(1024,780));//: Sets the size of the window.
	window.setPosition(sf::Vector2i(0,0));//: Sets the position of the window on the screen.
	window.setMouseCursorVisible(false);//: Sets the visibility of the mouse cursor in the window.
	window.setVerticalSyncEnabled(true);//: Enables or disables vertical synchronization.
	sf::View view(sf::FloatRect(0, 0, 800, 600)); // Define a view with the same size as the window
	window.setView(view); // Set the view for the window
	window.setActive(true);
	auto contextSettings = window.getSettings();//: Retrieves the current OpenGL context settings of the window.
	auto activeContext = sf::Context::getActiveContext();//: Retrieves the currently active OpenGL context.

    sf::CircleShape circleShape(55);
    while (window.isOpen())
    {
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::MouseButtonPressed ||
				event.type == sf::Event::MouseButtonReleased ||
				event.type == sf::Event::KeyPressed ||
				event.type == sf::Event::KeyReleased ||
				event.type == sf::Event::TextEntered ||
				event.type == sf::Event::MouseWheelScrolled ||
				event.type == sf::Event::MouseMoved ||
				event.type == sf::Event::MouseWheelMoved)
					input.HandleInputEvent(event.type);
        }

        window.clear();
        input.HandleInput();
        window.draw(circleShape);
        window.display();
    }
    return 0;
}
