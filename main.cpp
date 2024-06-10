#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Header/Logger.h"
#include "Header/Entity.h"
#include "Header/Scene.h"
#include "Header/Window.h"

int main()
{
	sf::RenderWindow& window = Window::createWindow(sf::VideoMode(1740,1000), "Alpha Squadron", sf::Style::None);
    Scene gameManager;

    sf::Clock clock;
	float timeElapsed = 0;
	int frameCount = 0;

    while (window.isOpen())
    {
		frameCount++;
		timeElapsed += clock.getElapsedTime().asSeconds();

		if(timeElapsed>=1)
		{
			Logger::Log(Verbose, "FPS: " + std::to_string(frameCount));
			frameCount = 0;
			timeElapsed = 0;
		}

		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::Resized)
			{
				Logger::Log(LogType::Verbose,"Window resized to " + std::to_string(event.size.width) + "x" + std::to_string(event.size.height));
			}

			if (event.type == sf::Event::LostFocus)
			{
				Logger::Log(LogType::Verbose,"Window lost focus");
			}

			if (event.type == sf::Event::GainedFocus)
			{
				Logger::Log(LogType::Verbose,"Window gained focus");
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)
				return 0;

            if (event.type == sf::Event::JoystickConnected ||
				event.type == sf::Event::JoystickDisconnected ||
				event.type == sf::Event::JoystickMoved ||
				event.type == sf::Event::TouchMoved ||
				event.type == sf::Event::SensorChanged ||
				event.type == sf::Event::TextEntered ||
				event.type == sf::Event::MouseWheelScrolled ||
				event.type == sf::Event::MouseMoved ||
				event.type == sf::Event::MouseWheelMoved)
					continue;
        }
		gameManager.update(clock.restart().asSeconds());
        window.clear();
		gameManager.render(window);
        window.display();
    }
    return 0;
}
