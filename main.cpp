#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Header/Logger.h"
#include "Header/Entity.h"
#include "Header/Scene.h"
#include "Header/Debug.h"
#include "Header/Game.h"

int main()
{
	sf::RenderWindow& window = Game::createWindow(sf::VideoMode(1740,1000), "Alpha Squadron", sf::Style::None);
    Scene scene;
	Debug::init();
	sf::Clock clock;
	sf::RenderStates states;

    while (window.isOpen())
    {

		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::Resized)
			{
				Logger::log(LogType::Verbose,"Window resized to " + std::to_string(event.size.width) + "x" + std::to_string(event.size.height));
			}

			if (event.type == sf::Event::LostFocus)
			{
				Logger::log(LogType::Verbose,"Window lost focus");
			}

			if (event.type == sf::Event::GainedFocus)
			{
				Logger::log(LogType::Verbose,"Window gained focus");
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Escape)
				return 0;

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::F)
				Debug::toggleFps();

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
		auto deltaTime = clock.restart().asSeconds();
		scene.update(deltaTime);
		Debug::update(deltaTime);
		window.clear();
		scene.render(window, states);
		Debug::render(window);
        window.display();
    }
    return 0;
}
