//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef SFML_CORE_HEADER_INPUT_H_
#define SFML_CORE_HEADER_INPUT_H_

#include <functional>
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window.hpp>
#include <queue>
#include "InputData.h"

namespace SfmlCoreInput
{
	class Input
	{
	 public:
		Input(bool isKeyboardEnabled, bool mouseEnabled, bool joystickEnabled, bool touchEnabled, bool sensorEnabled);

		using ActionDelegate = std::function<void()>;

		void HandleInput();

		static void Subscribe(int keyId, Input::ActionDelegate& delegate, const bool& onRelease = false);
		static void Unsubscribe(int keyId);
		static void ClearAll();

		static bool GetKeyboardEnabledState() { return keyboardEnabled; }
		static bool GetMouseEnabledState() { return mouseEnabled; }
		static bool GetJoystickEnabledState() { return joystickEnabled; }
		static bool GetTouchEnabledState() { return touchEnabled; }
		static bool GetSensorEnabledState() { return sensorEnabled; }

		static void SetKeyboardEnabledState(bool isEnabled) { keyboardEnabled = isEnabled; }
		static void SetMouseEnabledState(bool isEnabled) { mouseEnabled = isEnabled; }
		static void SetJoystickEnabledState(bool isEnabled) { joystickEnabled = isEnabled; }
		static void SetTouchEnabledState(bool isEnabled) { touchEnabled = isEnabled; }
		static void SetSensorEnabledState(bool isEnabled) { sensorEnabled = isEnabled; }

	 private:
		static std::unordered_map<int, InputData> keyDelegates;
		static bool keyboardEnabled;
		static bool mouseEnabled;
		static bool joystickEnabled;
		static bool touchEnabled;
		static bool sensorEnabled;
	};
}
#endif //SFML_CORE_HEADER_INPUT_H_
