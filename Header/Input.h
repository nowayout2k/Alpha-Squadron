#ifndef SFML_CORE_HEADER_INPUT_H_
#define SFML_CORE_HEADER_INPUT_H_

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Touch.hpp>
#include <SFML/Window/Sensor.hpp>
#include <vector>
#include <functional>

namespace SfmlCoreInput
{
    class Input
    {
    public:
        using ActionDelegate = std::function<void()>;
        using IntPositionDelegate = std::function<void(const sf::Vector2f&)>;
		using FloatPositionDelegate = std::function<void(const sf::Vector2f&)>;
        using AccelerationDelegate = std::function<void(const sf::Vector3f&)>;

        Input(bool isKeyboardEnabled, bool isMouseEnabled, bool isJoystickEnabled, bool isTouchEnabled, bool isSensorEnabled);

        void HandleInput();

        void SubscribeKey(sf::Keyboard::Key key, const ActionDelegate& delegate, bool onRelease = false);
        void SubscribeJoystickButton(unsigned int button, const FloatPositionDelegate& delegate);
        void SubscribeMouseButton(sf::Mouse::Button button, const IntPositionDelegate& delegate);
        void SubscribeTouchEvent(unsigned int touchCount, const IntPositionDelegate& delegate);
        void SubscribeSensorEvent(sf::Sensor::Type sensor, const AccelerationDelegate& delegate);

        void UnsubscribeKey(sf::Keyboard::Key key);
        void UnsubscribeJoystickButton(unsigned int button);
        void UnsubscribeMouseButton(sf::Mouse::Button button);
        void UnsubscribeTouchEvent(unsigned int touchCount);
        void UnsubscribeSensorEvent(sf::Sensor::Type sensor);

        void ClearAll();

    private:
        struct KeyInputData
        {
            sf::Keyboard::Key key;
            ActionDelegate delegate;
            bool onRelease;

            KeyInputData(sf::Keyboard::Key k, const ActionDelegate& d, bool release) : key(k), delegate(d), onRelease(release) {}
        };

        struct JoystickInputData
        {
            unsigned int button;
			FloatPositionDelegate delegate;

            JoystickInputData(unsigned int b, const FloatPositionDelegate& d) : button(b), delegate(d) {}
        };

        struct MouseInputData
        {
            sf::Mouse::Button button;
			IntPositionDelegate delegate;

            MouseInputData(sf::Mouse::Button b, const IntPositionDelegate& d) : button(b), delegate(d) {}
        };

        struct TouchInputData
        {
            unsigned int touchCount;
			IntPositionDelegate delegate;

            TouchInputData(unsigned int count, const IntPositionDelegate& d) : touchCount(count), delegate(d) {}
        };

        struct SensorInputData
        {
            sf::Sensor::Type sensor;
            AccelerationDelegate delegate;

            SensorInputData(sf::Sensor::Type s, const AccelerationDelegate& d) : sensor(s), delegate(d) {}
        };

        std::vector<KeyInputData> keyDelegates;
        std::vector<JoystickInputData> joystickDelegates;
        std::vector<MouseInputData> mouseDelegates;
        std::vector<TouchInputData> touchDelegates;
        std::vector<SensorInputData> sensorDelegates;

        bool keyboardEnabled;
        bool mouseEnabled;
        bool joystickEnabled;
        bool touchEnabled;
        bool sensorEnabled;
    };
}

#endif // SFML_CORE_HEADER_INPUT_H_
