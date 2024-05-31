#include "../Header/Input.h"

std::vector<Input::KeyInputData> Input::keyDelegates;
std::vector<Input::JoystickInputData> Input::joystickDelegates;
std::vector<Input::MouseInputData> Input::mouseDelegates;
std::vector<Input::TouchInputData> Input::touchDelegates;
std::vector<Input::SensorInputData> Input::sensorDelegates;

std::vector<sf::Keyboard::Key> Input::pressedKeysThisFrame;
std::vector<int> Input::pressedJoystickButtonsThisFrame;
std::vector<sf::Mouse::Button> Input::pressedMouseButtonsThisFrame;
std::vector<int> Input::fingerIndicesThisFrame;

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
            if (sf::Keyboard::isKeyPressed(data.key))
            {
                data.delegate(Input::pressedKeysThisFrame);
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
                data.delegate(position, Input::pressedJoystickButtonsThisFrame);
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
                data.delegate(position, Input::pressedMouseButtonsThisFrame);
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
                    data.delegate(position, fingerIndicesThisFrame);
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

void Input::SubscribeKey(sf::Keyboard::Key key, const KeyInputDelegate& delegate)
{
    keyDelegates.emplace_back(key, delegate);
}

void Input::SubscribeJoystickButton(unsigned int button, const JoystickInputDelegate& delegate)
{
    joystickDelegates.emplace_back(button, delegate);
}

void Input::SubscribeMouseButton(sf::Mouse::Button button, const MouseInputDelegate& delegate)
{
    mouseDelegates.emplace_back(button, delegate);
}

void Input::SubscribeTouchEvent(unsigned int touchCount, const TouchInputDelegate& delegate)
{
    touchDelegates.emplace_back(touchCount, delegate);
}

void Input::SubscribeSensorEvent(sf::Sensor::Type sensor, const SensorInputDelegate& delegate)
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

void Input::ClearAllDelegates()
{
    keyDelegates.clear();
    joystickDelegates.clear();
    mouseDelegates.clear();
    touchDelegates.clear();
    sensorDelegates.clear();
}

void Input::HandleMouseButtonPressedEvent(sf::Mouse::Button button)
{
    pressedMouseButtonsThisFrame.push_back(button);
}

void Input::HandleKeyPressedEvent(sf::Keyboard::Key key)
{
    pressedKeysThisFrame.push_back(key);
}

void Input::HandleTouchStartEvent(int fingerIndex)
{
    fingerIndicesThisFrame.push_back(fingerIndex);
}

void Input::HandleJoystickPressedEvent(int button)
{
    pressedJoystickButtonsThisFrame.push_back(button);
}

void Input::HandleMouseButtonReleasedEvent(sf::Mouse::Button button)
{
    std::remove(pressedMouseButtonsThisFrame.begin(), pressedMouseButtonsThisFrame.end(), button);
}

void Input::HandleKeyReleasedEvent(sf::Keyboard::Key key)
{
    std::remove(pressedKeysThisFrame.begin(), pressedKeysThisFrame.end(), key);
}

void Input::HandleTouchEndEvent(int fingerIndex)
{
    std::remove(fingerIndicesThisFrame.begin(), fingerIndicesThisFrame.end(), fingerIndex);
}

void Input::HandleJoystickReleasedEvent(int button)
{
    std::remove(pressedJoystickButtonsThisFrame.begin(), pressedJoystickButtonsThisFrame.end(),button);
}

