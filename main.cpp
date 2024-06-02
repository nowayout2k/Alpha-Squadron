#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Header/Logger.h"
#include "Header/Entity.h"
#include "Header/GameManager.h"
#include "Header/WindowManager.h"

int main()
{
	sf::RenderWindow& window = WindowManager::createWindow(sf::VideoMode(800, 600), "Alpha Squadron", sf::Style::Close);
    GameManager gameManager;

    sf::Clock clock;
    while (window.isOpen())
    {
        clock.restart();
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
		gameManager.update(clock.getElapsedTime().asSeconds());
        window.clear();
		gameManager.render(window);
        window.display();
    }
    return 0;
}
