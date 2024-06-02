#ifndef SFML_CORE_HEADER_INPUT_H_
#define SFML_CORE_HEADER_INPUT_H_

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Touch.hpp>
#include <SFML/Window/Sensor.hpp>
#include <vector>
#include <functional>

class Input
{

    public:
        enum InputType
        {
            Unknown = -1,
            Keyboard = 0,
            Mouse = 1,
            Joystick = 2,
            Touch = 3,
            Sensor = 4
        };

        struct InputEventInfo
        {
            InputEventInfo(int inputValue, bool isHeldDown, bool isValid)
                    : InputValue(inputValue), IsHeldDown(isHeldDown), IsValid(isValid){};
            int InputValue;
            bool IsHeldDown;
            bool IsValid;
        };

        using KeyInputDelegate = std::function<void(std::vector<Input::InputEventInfo>& otherKeysPressed)>;
        using MouseInputDelegate = std::function<void(const sf::Vector2i&, std::vector<Input::InputEventInfo>& otherButtonsPressed)>;
        using TouchInputDelegate = std::function<void(const sf::Vector2i&, std::vector<Input::InputEventInfo>& fingerIndices)>;
        using JoystickInputDelegate = std::function<void(const sf::Vector2f&, std::vector<Input::InputEventInfo>& otherButtonsPressed)>;
        using SensorInputDelegate = std::function<void(const sf::Vector3f&)>;

        Input(bool isKeyboardEnabled, bool isMouseEnabled, bool isJoystickEnabled, bool isTouchEnabled, bool isSensorEnabled);

        void HandleInput();

        //Subscribe
        static void SubscribeKey(sf::Keyboard::Key key, const KeyInputDelegate& delegate);
        static void SubscribeJoystickButton(unsigned int button, const JoystickInputDelegate& delegate);
        static void SubscribeMouseButton(sf::Mouse::Button button, const MouseInputDelegate& delegate);
        static void SubscribeTouch(unsigned int fingerIndex, const TouchInputDelegate& delegate);
        static void SubscribeSensor(sf::Sensor::Type sensor, const SensorInputDelegate& delegate);

        //Unsubscribe
        static void UnsubscribeKey(sf::Keyboard::Key key);
        static void UnsubscribeJoystickButton(unsigned int button);
        static void UnsubscribeMouseButton(sf::Mouse::Button button);
        static void UnsubscribeTouch(unsigned int touchCount);
        static void UnsubscribeSensor(sf::Sensor::Type sensor);

        static void ClearAllDelegates();

        static void HandlePressedEvent(Input::InputType type, int inputValue);
        static void HandleReleasedEvent(Input::InputType type, int inputValue);
    private:
        struct KeyInputData
        {
            sf::Keyboard::Key key;
            KeyInputDelegate delegate;

            KeyInputData(sf::Keyboard::Key k, const KeyInputDelegate &d) : key(k), delegate(d) {}
        };

        struct JoystickInputData
        {
            unsigned int button;
            JoystickInputDelegate delegate;

            JoystickInputData(unsigned int b, const JoystickInputDelegate &d) : button(b), delegate(d) {}
        };

        struct MouseInputData
        {
            sf::Mouse::Button button;
            MouseInputDelegate delegate;

            MouseInputData(sf::Mouse::Button b, const MouseInputDelegate &d) : button(b), delegate(d) {}
        };

        struct TouchInputData
        {
            unsigned int fingerIndex;
            TouchInputDelegate delegate;

            TouchInputData(unsigned int fingerIndex, const TouchInputDelegate &d) : fingerIndex(fingerIndex), delegate(d) {}
        };

        struct SensorInputData
        {
            sf::Sensor::Type sensor;
            SensorInputDelegate delegate;

            SensorInputData(sf::Sensor::Type s, const SensorInputDelegate &d) : sensor(s), delegate(d) {}
        };

        std::string to_string(InputType e)
        {
            switch (e)
            {
                case InputType::Unknown:
                    return "Unknown";
                case InputType::Keyboard:
                    return "Keyboard";
                case InputType::Joystick:
                    return "Joystick";
                case InputType::Touch:
                    return "Touch";
                case InputType::Sensor:
                    return "Sensor";
                default:
                    return "Unknown";
            }
        }

        static void ClearIdCaches();
        static void CheckAllInputValidity();
        static void CheckInputValidity(std::vector<Input::InputEventInfo>* inputThisFrame);

        static std::string GenerateID(InputType inputType, const int& input);
        static std::string GetHash(InputType inputType, const int& input);

        static std::unordered_map<std::string, KeyInputData> keyDelegates;
        static std::unordered_map<std::string, JoystickInputData> joystickDelegates;
        static std::unordered_map<std::string, MouseInputData> mouseDelegates;
        static std::unordered_map<std::string, TouchInputData> touchDelegates;
        static std::unordered_map<std::string, SensorInputData> sensorDelegates;

        static std::unordered_map<int, std::string> keyboardIdCache;
        static std::unordered_map<int, std::string> joystickIdCache;
        static std::unordered_map<int, std::string> mouseIdCache;
        static std::unordered_map<int, std::string> touchIdCache;

        static std::vector<InputEventInfo> pressedKeysThisFrame;
        static std::vector<InputEventInfo> pressedJoystickButtonsThisFrame;
        static std::vector<InputEventInfo> pressedMouseButtonsThisFrame;
        static std::vector<InputEventInfo> fingerIndicesThisFrame;

        static bool keyboardEnabled;
        static bool mouseEnabled;
        static bool joystickEnabled;
        static bool touchEnabled;
        static bool sensorEnabled;
};

#endif // SFML_CORE_HEADER_INPUT_H_
