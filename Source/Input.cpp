#include "../Header/Input.h"

std::vector<Input::KeyInputData> Input::keyDelegates;
std::vector<Input::JoystickInputData> Input::joystickDelegates;
std::vector<Input::MouseInputData> Input::mouseDelegates;
std::vector<Input::TouchInputData> Input::touchDelegates;
std::vector<Input::SensorInputData> Input::sensorDelegates;

bool Input::keyboardEnabled = false;
bool Input::mouseEnabled = false;
bool Input::joystickEnabled = false;
bool Input::touchEnabled = false;
bool Input::sensorEnabled = false;

Input::Input(bool isKeyboardEnabled, bool isMouseEnabled, bool isJoystickEnabled, bool isTouchEnabled, bool isSensorEnabled)
{
    keyboardEnabled = isKeyboardEnabled;
    mouseEnabled = isMouseEnabled;
    joystickEnabled = isJoystickEnabled;
    touchEnabled = isTouchEnabled;
    sensorEnabled = isSensorEnabled;
}

void Input::HandleInput()
{
    if (keyboardEnabled)
    {
        for (const auto& data : keyDelegates)
        {
            if ((data.onRelease && !sf::Keyboard::isKeyPressed(data.key)) ||
                (!data.onRelease && sf::Keyboard::isKeyPressed(data.key)))
            {
                data.delegate();
            }
        }
    }

    if (joystickEnabled && sf::Joystick::isConnected(0))
    {
        for (const auto& data : joystickDelegates)
        {
            sf::Vector2f position(sf::Joystick::getAxisPosition(0, sf::Joystick::X),
                                  sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
            if (sf::Joystick::isButtonPressed(0, data.button))
            {
                data.delegate(position);
            }
        }
    }

    if (mouseEnabled)
    {
        sf::Vector2i position = sf::Mouse::getPosition();
        for (const auto& data : mouseDelegates)
        {
            if (sf::Mouse::isButtonPressed(data.button))
            {
                data.delegate(position);
            }
        }
    }

    if (touchEnabled)
    {
        for (unsigned int touchCount = 0; touchCount < 5; ++touchCount)
        {
            sf::Vector2i position = sf::Touch::getPosition(touchCount);
            for (const auto& data : touchDelegates)
            {
                if (data.touchCount == touchCount)
                {
                    data.delegate(position);
                }
            }
        }
    }

    if (sensorEnabled)
    {
        for (const auto& data : sensorDelegates)
        {
            sf::Vector3f acceleration = sf::Sensor::getValue(data.sensor);
            data.delegate(acceleration);
        }
    }
}

void Input::SubscribeKey(sf::Keyboard::Key key, const ActionDelegate& delegate, bool onRelease)
{
    keyDelegates.emplace_back(key, delegate, onRelease);
}

void Input::SubscribeJoystickButton(unsigned int button, const FloatPositionDelegate& delegate)
{
    joystickDelegates.emplace_back(button, delegate);
}

void Input::SubscribeMouseButton(sf::Mouse::Button button, const IntPositionDelegate& delegate)
{
    mouseDelegates.emplace_back(button, delegate);
}

void Input::SubscribeTouchEvent(unsigned int touchCount, const IntPositionDelegate& delegate)
{
    touchDelegates.emplace_back(touchCount, delegate);
}

void Input::SubscribeSensorEvent(sf::Sensor::Type sensor, const AccelerationDelegate& delegate)
{
    sensorDelegates.emplace_back(sensor, delegate);
}

void Input::UnsubscribeKey(sf::Keyboard::Key key)
{
    keyDelegates.erase(std::remove_if(keyDelegates.begin(), keyDelegates.end(),[key](const auto& data) { return data.key == key; }),keyDelegates.end());
}

void Input::UnsubscribeJoystickButton(unsigned int button)
{
    joystickDelegates.erase(std::remove_if(joystickDelegates.begin(), joystickDelegates.end(),[button](const auto& data) { return data.button == button; }),joystickDelegates.end());
}

void Input::UnsubscribeMouseButton(sf::Mouse::Button button)
{
    mouseDelegates.erase(std::remove_if(mouseDelegates.begin(), mouseDelegates.end(),[button](const auto& data) { return data.button == button; }),mouseDelegates.end());
}

void Input::UnsubscribeTouchEvent(unsigned int touchCount)
{
    touchDelegates.erase(std::remove_if(touchDelegates.begin(), touchDelegates.end(),[touchCount](const auto& data) { return data.touchCount == touchCount; }),touchDelegates.end());
}

void Input::UnsubscribeSensorEvent(sf::Sensor::Type sensor)
{
    sensorDelegates.erase(std::remove_if(sensorDelegates.begin(), sensorDelegates.end(),[sensor](const auto& data) { return data.sensor == sensor; }),sensorDelegates.end());
}

void Input::ClearAll()
{
    keyDelegates.clear();
    joystickDelegates.clear();
    mouseDelegates.clear();
    touchDelegates.clear();
    sensorDelegates.clear();
}

