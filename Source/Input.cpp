//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Input.h"

namespace SfmlCoreInput
{
	std::unordered_map<int, InputData> Input::keyDelegates;
	InputData Input::mouseButtonPressedData;
	InputData Input::mouseButtonReleasedData;
	InputData Input::mouseWheelScrolledData;
	InputData Input::mouseMovedData;
	InputData Input::mouseWheelMovedData;
	InputData Input::keyPressedData;
	InputData Input::keyReleasedData;
	InputData Input::textEnteredData;

	Input::Input()
	{
		bMouseButtonPressed = false;
		bMouseButtonReleased = false;
		bKeyPressed = false;
		bKeyReleased = false;
		bTextEntered = false;
		bMouseWheelScrolled = false;
		bMouseMoved = false;
		bMouseWheelMoved = false;
	}

	void Input::HandleInput() // NOLINT(*-convert-member-functions-to-static)
	{
		for (const auto& pair : keyDelegates)
		{
			if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(pair.first)))
			{

				if(pair.second.delegate != nullptr)
					pair.second.delegate(); // Call the delegate function
			}
		}

		bMouseButtonPressed = false;
		bMouseButtonReleased = false;
		bKeyPressed = false;
		bKeyReleased = false;
		bTextEntered = false;
		bMouseWheelScrolled = false;
		bMouseMoved = false;
		bMouseWheelMoved = false;
	}

	void Input::HandleInputEvent(sf::Event::EventType eventType)
	{
		if (eventType == sf::Event::MouseButtonPressed)
			bMouseButtonPressed = true;
		if (eventType == sf::Event::MouseButtonReleased)
			bMouseButtonReleased = true;
		if (eventType == sf::Event::KeyPressed)
			bKeyPressed = true;
		if (eventType == sf::Event::KeyReleased)
			bKeyReleased = true;
		if (eventType == sf::Event::TextEntered)
			bTextEntered = true;
		if (eventType == sf::Event::MouseWheelScrolled)
			bMouseWheelScrolled = true;
		if (eventType == sf::Event::MouseMoved)
			bMouseMoved = true;
		if (eventType == sf::Event::MouseWheelMoved)
			bMouseWheelMoved = true;
	}

	void Input::ClearAll()
	{
		keyDelegates.clear();
	}

	void Input::SubscribeToKey(sf::Keyboard::Key key, const Input::ActionDelegate& delegate, const bool& onRelease)
	{
		auto keyInt = static_cast<int>(key);

		InputData data;
		if(onRelease)
			data = InputData(sf::Keyboard::KeyCount + 2, delegate, true);
		else
			data = InputData(sf::Keyboard::KeyCount + 1, delegate, false);

		keyDelegates[data.keyId] = data;
	}

	void Input::UnsubscribeFromKey(sf::Keyboard::Key key)
	{
		auto keyInt = static_cast<int>(key);
		auto iter = keyDelegates.find(keyInt);
		if (iter != keyDelegates.end())
			keyDelegates.erase(iter);
	}

	void Input::SubscribeToMouseClick(Input::ActionDelegate& delegate, const bool onRelease)
	{
		if(onRelease)
			mouseButtonReleasedData = InputData(sf::Keyboard::KeyCount + 4, delegate, true);
		else
			mouseButtonPressedData = InputData(sf::Keyboard::KeyCount + 3, delegate, false);
	}

	void Input::UnsubscribeToMouseClick(const Input::ActionDelegate& delegate)
	{
		mouseButtonPressedData = InputData();
		mouseButtonReleasedData = InputData();
	}

	void Input::SubscribeToMouseMove(const Input::ActionDelegate& delegate)
	{
		mouseMovedData = InputData(sf::Keyboard::KeyCount + 5, delegate, false);
	}

	void Input::UnsubscribeToMouseMove()
	{
		mouseMovedData = InputData();
	}

	void Input::SubscribeToMouseWheelMoved(const Input::ActionDelegate& delegate)
	{
		mouseWheelMovedData = InputData(sf::Keyboard::KeyCount + 6, delegate, false);
	}

	void Input::UnsubscribeToMouseWheelMoved()
	{
		mouseWheelMovedData = InputData();
	}

	void Input::SubscribeToMouseWheelScrolled(const Input::ActionDelegate& delegate)
	{
		mouseWheelScrolledData = InputData(sf::Keyboard::KeyCount + 7, delegate, false);
	}

	void Input::UnsubscribeToMouseWheelScrolled()
	{
		mouseWheelScrolledData = InputData();
	}

	void Input::SubscribeToTextEntered(const Input::ActionDelegate& delegate)
	{
		textEnteredData = InputData(sf::Keyboard::KeyCount + 8, delegate, false);
	}

	void Input::UnsubscribeToTextEntered()
	{
		textEnteredData = InputData();
	}
}