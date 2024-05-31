#ifndef SFML_CORE_HEADER_INPUT_H_
#define SFML_CORE_HEADER_INPUT_H_

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Touch.hpp>
#include <SFML/Window/Sensor.hpp>
#include <vector>
#include <functional>

class Input {
    public:
        using KeyInputDelegate = std::function<void(std::vector<sf::Keyboard::Key>& otherKeysPressed)>;
        using MouseInputDelegate = std::function<void(const sf::Vector2i&, std::vector<sf::Mouse::Button>& otherButtonsPressed)>;
        using TouchInputDelegate = std::function<void(const sf::Vector2i&, std::vector<int> fingerIndices)>;
        using JoystickInputDelegate = std::function<void(const sf::Vector2f&, std::vector<int>& otherButtonsPressed)>;
        using SensorInputDelegate = std::function<void(const sf::Vector3f&)>;

        Input(bool isKeyboardEnabled, bool isMouseEnabled, bool isJoystickEnabled, bool isTouchEnabled,
              bool isSensorEnabled);

        void HandleInput();

        //input Event Handlers
        void HandleMouseButtonPressedEvent();
        void HandleKeyPressedEvent();
        void HandleTouchEvent();
        void HandleJoystickEvent();

        //Subscribe
        static void SubscribeKey(sf::Keyboard::Key key, const KeyInputDelegate& delegate);
        static void SubscribeJoystickButton(unsigned int button, const JoystickInputDelegate& delegate);
        static void SubscribeMouseButton(sf::Mouse::Button button, const MouseInputDelegate& delegate);
        static void SubscribeTouchEvent(unsigned int touchCount, const TouchInputDelegate& delegate);
        static void SubscribeSensorEvent(sf::Sensor::Type sensor, const SensorInputDelegate& delegate);

        //Unsubscribe
        static void UnsubscribeKey(sf::Keyboard::Key key);
        static void UnsubscribeJoystickButton(unsigned int button);
        static void UnsubscribeMouseButton(sf::Mouse::Button button);
        static void UnsubscribeTouchEvent(unsigned int touchCount);
        static void UnsubscribeSensorEvent(sf::Sensor::Type sensor);

        static void ClearAllDelegates();

        static void HandleMouseButtonPressedEvent(sf::Mouse::Button button);
        static void HandleKeyPressedEvent(sf::Keyboard::Key key);
        static void HandleTouchStartEvent(int fingerIndex);
        static void HandleJoystickPressedEvent(int button);

        static void HandleMouseButtonReleasedEvent(sf::Mouse::Button button);
        static void HandleKeyReleasedEvent(sf::Keyboard::Key key);
        static void HandleTouchEndEvent(int fingerIndex);
        static void HandleJoystickReleasedEvent(int button);

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
            unsigned int touchCount;
            TouchInputDelegate delegate;

            TouchInputData(unsigned int count, const TouchInputDelegate &d) : touchCount(count), delegate(d) {}
        };

        struct SensorInputData
        {
            sf::Sensor::Type sensor;
            SensorInputDelegate delegate;

            SensorInputData(sf::Sensor::Type s, const SensorInputDelegate &d) : sensor(s), delegate(d) {}
        };

        static std::vector<KeyInputData> keyDelegates;
        static std::vector<JoystickInputData> joystickDelegates;
        static std::vector<MouseInputData> mouseDelegates;
        static std::vector<TouchInputData> touchDelegates;
        static std::vector<SensorInputData> sensorDelegates;

        static std::vector<sf::Keyboard::Key> pressedKeysThisFrame;
        static std::vector<int> pressedJoystickButtonsThisFrame;
        static std::vector<sf::Mouse::Button> pressedMouseButtonsThisFrame;
        static std::vector<int> fingerIndicesThisFrame;

        static bool keyboardEnabled;
        static bool mouseEnabled;
        static bool joystickEnabled;
        static bool touchEnabled;
        static bool sensorEnabled;
};

#endif // SFML_CORE_HEADER_INPUT_H_
