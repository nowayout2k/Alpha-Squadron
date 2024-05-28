//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Input.h"
#include "../Header/Graphics.h"

namespace SfmlCoreInput
{
	std::unordered_map<int, InputData> Input::keyDelegates;

	Input::Input(bool isKeyboardEnabled, bool isMouseEnabled, bool isJoystickEnabled, bool isTouchEnabled, bool isSensorEnabled)
	{
		Input::keyboardEnabled = isKeyboardEnabled;
		Input::mouseEnabled = isMouseEnabled;
		Input::joystickEnabled = isJoystickEnabled;
		Input::touchEnabled = isTouchEnabled;
		Input::sensorEnabled = isSensorEnabled;
	}

	void Input::HandleInput() // NOLINT(*-convert-member-functions-to-static)
	{
		for (const auto& pair : keyDelegates)
		{
			if (keyboardEnabled && sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(pair.first)))
			{
				if (pair.second.delegate != nullptr)
					pair.second.delegate(); // Call the delegate function
			}

			unsigned int joystickId = 0;
			if (joystickEnabled && sf::Joystick::isConnected(joystickId))
			{
				// Check if a specific button is pressed
				if (sf::Joystick::isButtonPressed(joystickId, sf::Joystick::))
				{

				}
				float x = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X);
				float y = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y);
			}

			if (mouseEnabled)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(Graphics::GetCurrentWindow());
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{

				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
				{

				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{

				}
			}

			if (touchEnabled)
			{
				unsigned int finger = 0;
				if(sf::Touch::isDown(finger))
				{
					sf::Vector2i position = sf::Touch::getPosition(finger, Graphics::GetCurrentWindow());
				}
			}

			if (sensorEnabled && sf::Sensor::isAvailable(sf::Sensor::Accelerometer))
			{
				sf::Vector3f acceleration = sf::Sensor::getValue(sf::Sensor::Accelerometer);
			}
		}

	}

	void Input::ClearAll()
	{
		keyDelegates.clear();
	}

	void Input::Subscribe(int id, Input::ActionDelegate& delegate, const bool& onRelease)
	{
		InputData data;
		if(onRelease)
			data = InputData(id, delegate, true);
		else
			data = InputData(id + sf::Keyboard::KeyCount, delegate, false);

		keyDelegates[data.id] = data;
	}

	void Input::Unsubscribe(int id)
	{
		auto iter = keyDelegates.find(id);
		if (iter != keyDelegates.end())
			keyDelegates.erase(iter);
	}
}