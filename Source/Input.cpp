#include "../Header/Input.h"

std::unordered_map<std::string, Input::KeyInputData> Input::keyDelegates;
std::unordered_map<std::string, Input::JoystickInputData> Input::joystickDelegates;
std::unordered_map<std::string, Input::MouseInputData> Input::mouseDelegates;
std::unordered_map<std::string, Input::TouchInputData> Input::touchDelegates;
std::unordered_map<std::string, Input::SensorInputData> Input::sensorDelegates;

std::unordered_map<sf::Keyboard::Key, std::string> Input::keyboardIdCache;
std::unordered_map<int, std::string> Input::joystickIdCache;
std::unordered_map<sf::Mouse::Button, std::string> Input::mouseIdCache;
std::unordered_map<int, std::string> Input::touchIdCache;

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
        for (const auto& key : Input::pressedKeysThisFrame)
        {
            std::string id = GenerateID(InputType::Keyboard, key);
            auto it = keyDelegates.find(id);
            if (it != keyDelegates.end())
            {
                it->second.delegate(Input::pressedKeysThisFrame);
            }
        }
    }

    if (joystickEnabled && sf::Joystick::isConnected(0))
    {
        for (const auto& button : Input::pressedJoystickButtonsThisFrame)
        {
            sf::Vector2f position(sf::Joystick::getAxisPosition(0, sf::Joystick::X),
                                  sf::Joystick::getAxisPosition(0, sf::Joystick::Y));

            std::string id = GenerateID(InputType::Joystick, button);
            auto it = joystickDelegates.find(id);
            if (it != joystickDelegates.end())
            {
                it->second.delegate(position, Input::pressedJoystickButtonsThisFrame);
            }
        }
    }

    if (mouseEnabled)
    {
        sf::Vector2i position = sf::Mouse::getPosition();
        for (const auto& button : Input::pressedMouseButtonsThisFrame)
        {
            std::string id = GenerateID(InputType::Mouse, button);
            auto it = mouseDelegates.find(id);
            if (it != mouseDelegates.end())
            {
                it->second.delegate(position, Input::pressedMouseButtonsThisFrame);
            }
        }
    }

    if (touchEnabled)
    {
        for (const auto& fingerIndex : Input::fingerIndicesThisFrame)
        {
            std::string id = GenerateID(InputType::Touch, fingerIndex);
            auto it = touchDelegates.find(id);
            sf::Vector2i position = sf::Touch::getPosition(fingerIndex);
            if (it != touchDelegates.end())
            {
                it->second.delegate(position, Input::fingerIndicesThisFrame);
            }
        }
    }

    if (sensorEnabled)
    {
        for (const auto& data : sensorDelegates)
        {
            sf::Vector3f acceleration = sf::Sensor::getValue(data.second.sensor);
            data.second.delegate(acceleration);
        }
    }
}

void Input::SubscribeKey(sf::Keyboard::Key key, const KeyInputDelegate& delegate)
{
    std::string id = GenerateID(InputType::Keyboard, key);
    auto data = KeyInputData(key, delegate);
    auto itr = keyDelegates.find(id);
    if (itr != keyDelegates.end())
        itr->second = data;
    else
        keyDelegates.emplace(id, data);
}

void Input::SubscribeJoystickButton(unsigned int button, const JoystickInputDelegate& delegate)
{
    std::string id = GenerateID(InputType::Joystick, button);
    auto data = JoystickInputData(button, delegate);
    auto itr = joystickDelegates.find(id);
    if (itr != joystickDelegates.end())
        itr->second = data;
    else
        joystickDelegates.emplace(id, data);
}

void Input::SubscribeMouseButton(sf::Mouse::Button button, const MouseInputDelegate& delegate)
{
    std::string id = GenerateID(InputType::Mouse, button);
    auto data = MouseInputData(button, delegate);
    auto itr = mouseDelegates.find(id);
    if (itr != mouseDelegates.end())
        itr->second = data;
    else
        mouseDelegates.emplace(id, data);
}

void Input::SubscribeTouch(unsigned int fingerIndex, const TouchInputDelegate& delegate)
{
    std::string id = GenerateID(InputType::Touch, fingerIndex);
    auto data = TouchInputData(fingerIndex, delegate);
    auto itr = touchDelegates.find(id);
    if (itr != touchDelegates.end())
        itr->second = data;
    else
        touchDelegates.emplace(id, data);
}

void Input::SubscribeSensor(sf::Sensor::Type sensor, const SensorInputDelegate& delegate)
{
    std::string id = GenerateID(InputType::Sensor, sensor);
    auto data = SensorInputData(sensor, delegate);
    auto itr = sensorDelegates.find(id);
    if (itr != sensorDelegates.end())
        itr->second = data;
    else
        sensorDelegates.emplace(id, data);
}

void Input::UnsubscribeKey(sf::Keyboard::Key key)
{
    std::string id = GenerateID(InputType::Keyboard, key);
    keyDelegates.erase(id);
}

void Input::UnsubscribeJoystickButton(unsigned int button)
{
    std::string id = GenerateID(InputType::Joystick, button);
    joystickDelegates.erase(id);
}

void Input::UnsubscribeMouseButton(sf::Mouse::Button button)
{
    std::string id = GenerateID(InputType::Mouse, button);
    mouseDelegates.erase(id);
}

void Input::UnsubscribeTouch(unsigned int fingerIndex)
{
    std::string id = GenerateID(InputType::Touch, fingerIndex);
    touchDelegates.erase(id);
}

void Input::UnsubscribeSensor(sf::Sensor::Type sensor)
{
    std::string id = GenerateID(InputType::Sensor, sensor);
    sensorDelegates.erase(id);
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

void Input::ClearIdCaches()
{
    keyboardIdCache.clear();
    joystickIdCache.clear();
    mouseIdCache.clear();
    touchIdCache.clear();
}

template<typename T>
std::string Input::GenerateID(InputType inputType, const T &input)
{
    std::string hash;
    switch(inputType)
    {
        case InputType::Keyboard:
            if(keyboardIdCache.find(input) != keyboardIdCache.end())
                return keyboardIdCache[input];
            keyboardIdCache[input] = hash;
            hash = GetHash(inputType, input);
            break;
        case InputType::Mouse:
            if(mouseIdCache.find(input) != mouseIdCache.end())
                return mouseIdCache[input];
            mouseIdCache[input] = hash;
            hash = GetHash(inputType, input);
            break;
        case InputType::Joystick:
            if(joystickIdCache.find(input) != joystickIdCache.end())
                return joystickIdCache[input];
            joystickIdCache[input] = hash;
            hash = GetHash(inputType, input);
            break;
        case InputType::Touch:
            if(touchIdCache.find(input) != touchIdCache.end())
                return touchIdCache[input];
            touchIdCache[input] = hash;
            hash = GetHash(inputType, input);
            break;
        case InputType::Sensor:
            hash = GetHash(inputType, input);
            break;
        case InputType::Unknown:
            hash = GetHash(inputType, input);
            break;
    }
    return hash;
}

template<typename T>
std::string Input::GetHash(InputType inputType, const T &input)
{
    // Serialize the input into a string
    std::string data = std::to_string(inputType) + std::to_string(input);

    // Use a hash function to generate a hash of the serialized data
    std::hash<std::string> hasher;
    size_t hashValue = hasher(data);

    // Convert hash value to a string
    return std::to_string(hashValue);
}

