//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef SFML_CORE_HEADER_INPUT_H_
#define SFML_CORE_HEADER_INPUT_H_

#include <functional>
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window.hpp>
#include "InputData.h"

namespace SfmlCoreInput
{
	class Input
	{
	 public:
		Input();

		using ActionDelegate = std::function<void()>;

		void HandleInput();
		void HandleInputEvent(sf::Event::EventType eventType);

		static void SubscribeToKey(sf::Keyboard::Key key, const Input::ActionDelegate& delegate, const bool& onRelease = false);
		static void UnsubscribeFromKey(sf::Keyboard::Key key);

		static void SubscribeToMouseClick(Input::ActionDelegate& delegate, const bool onRelease = false);
		static void UnsubscribeToMouseClick(const Input::ActionDelegate& delegate);

		static void SubscribeToMouseMove(const Input::ActionDelegate& delegate);
		static void UnsubscribeToMouseMove();

		static void SubscribeToMouseWheelMoved(const ActionDelegate& delegate);
		static void UnsubscribeToMouseWheelMoved();

		static void SubscribeToMouseWheelScrolled(const ActionDelegate& delegate);
		static void UnsubscribeToMouseWheelScrolled();

		static void SubscribeToTextEntered(const ActionDelegate& delegate);
		static void UnsubscribeToTextEntered();

		static void ClearAll();

	 private:
		static std::unordered_map<int, InputData> keyDelegates;
		static InputData mouseButtonPressedData;
		static InputData mouseButtonReleasedData;
		static InputData mouseWheelScrolledData;
		static InputData mouseMovedData;
		static InputData mouseWheelMovedData;
		static InputData keyPressedData;
		static InputData keyReleasedData;
		static InputData textEnteredData;

		bool bMouseButtonPressed;
		bool bMouseButtonReleased;
		bool bMouseWheelScrolled;
		bool bMouseMoved;
		bool bMouseWheelMoved;
		bool bKeyPressed;
		bool bKeyReleased;
		bool bTextEntered;
	};
}
#endif //SFML_CORE_HEADER_INPUT_H_
