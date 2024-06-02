#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Header/Input.h"
#include "Header/Logger.h"
#include "Header/Graphics.h"
#include "Header/Entity.h"
#include "Header/Player.h"
#include "Header/GameManager.h"
#include "Header/Utility.h"

int main()
{
	Graphics graphics;
	sf::RenderWindow& window = graphics.CreateWindow(sf::VideoMode(800, 600), "Alpha Squadron", sf::Style::Default);
    Input input(true, false, false, false, false);
    GameManager gameManager;

    while (window.isOpen())
    {
        window.clear();

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

            if(event.type == sf::Event::MouseButtonPressed)
            {
                Input::HandlePressedEvent(Input::InputType::Mouse, event.mouseButton.button);
            }

            if(event.type == sf::Event::MouseButtonReleased)
            {
                Input::HandleReleasedEvent(Input::InputType::Mouse,event.mouseButton.button);
            }

            if (event.type == sf::Event::JoystickButtonPressed)
            {
                Input::HandlePressedEvent(Input::InputType::Joystick,event.joystickButton.button);
            }
            if (event.type == sf::Event::JoystickButtonReleased)
            {
                Input::HandleReleasedEvent(Input::InputType::Joystick,event.joystickButton.button);
            }

            if (event.type == sf::Event::KeyPressed)
            {
                Input::HandlePressedEvent(Input::InputType::Keyboard,event.key.code);
            }
            if (event.type == sf::Event::KeyReleased)
            {
                Input::HandleReleasedEvent(Input::InputType::Keyboard,event.key.code);
            }

            if (event.type == sf::Event::TouchBegan)
            {
                Input::HandlePressedEvent(Input::InputType::Touch,event.touch.finger);
            }

            if (event.type == sf::Event::TouchEnded)
            {
                Input::HandleReleasedEvent(Input::InputType::Touch,event.touch.finger);
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
        input.HandleInput();
        window.draw(gameManager.player);
        window.display();
    }
    return 0;
}
