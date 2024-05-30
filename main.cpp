#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Header/Input.h"
#include "Header/Logger.h"
#include "Header/Graphics.h"
#include "Header/Entity.h"

int main()
{
	Graphics graphics;
	sf::RenderWindow& window = graphics.CreateWindow(sf::VideoMode(800, 600), "Alpha Squadron", sf::Style::Default);
    Input input(true, false, false, false, false);
	std::unique_ptr<sf::Drawable> entity;
	entity = std::make_unique<Entity>();

    while (window.isOpen())
    {
		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::Resized)
			{
				SfmlCoreUtility::Logger::Log(SfmlCoreUtility::LogType::Verbose,"Window resized to " + std::to_string(event.size.width) + "x" + std::to_string(event.size.height));
			}

			if (event.type == sf::Event::LostFocus)
			{
				SfmlCoreUtility::Logger::Log(SfmlCoreUtility::LogType::Verbose,"Window lost focus");
			}

			if (event.type == sf::Event::GainedFocus)
			{
				SfmlCoreUtility::Logger::Log(SfmlCoreUtility::LogType::Verbose,"Window gained focus");
			}

			if (event.type == sf::Event::JoystickConnected ||
				event.type == sf::Event::JoystickDisconnected ||
				event.type == sf::Event::JoystickButtonPressed ||
				event.type == sf::Event::JoystickButtonReleased ||
				event.type == sf::Event::JoystickMoved ||
				event.type == sf::Event::TouchBegan ||
				event.type == sf::Event::TouchMoved ||
				event.type == sf::Event::TouchEnded ||
				event.type == sf::Event::SensorChanged ||
				event.type == sf::Event::MouseButtonPressed ||
				event.type == sf::Event::MouseButtonReleased ||
				event.type == sf::Event::KeyPressed ||
				event.type == sf::Event::KeyReleased ||
				event.type == sf::Event::TextEntered ||
				event.type == sf::Event::MouseWheelScrolled ||
				event.type == sf::Event::MouseMoved ||
				event.type == sf::Event::MouseWheelMoved)
					continue;
        }

        window.clear();
        input.HandleInput();
        window.draw(*entity);
        window.display();
    }
    return 0;
}
