#include "../Header/Input.h"

std::unordered_map<std::string, Input::KeyInputData> Input::keyDelegates;
std::unordered_map<std::string, Input::JoystickInputData> Input::joystickDelegates;
std::unordered_map<std::string, Input::MouseInputData> Input::mouseDelegates;
std::unordered_map<std::string, Input::TouchInputData> Input::touchDelegates;
std::unordered_map<std::string, Input::SensorInputData> Input::sensorDelegates;

std::unordered_map<int, std::string> Input::keyboardIdCache;
std::unordered_map<int, std::string> Input::joystickIdCache;
std::unordered_map<int, std::string> Input::mouseIdCache;
std::unordered_map<int, std::string> Input::touchIdCache;

std::vector<Input::InputEventInfo> Input::pressedKeysThisFrame;
std::vector<Input::InputEventInfo> Input::pressedJoystickButtonsThisFrame;
std::vector<Input::InputEventInfo> Input::pressedMouseButtonsThisFrame;
std::vector<Input::InputEventInfo> Input::fingerIndicesThisFrame;

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
        for (const auto& inputEventInfo : Input::pressedKeysThisFrame)
        {
            std::string id = GenerateID(InputType::Keyboard, inputEventInfo.InputValue);
            auto it = keyDelegates.find(id);
            if (it != keyDelegates.end())
            {
                it->second.delegate(Input::pressedKeysThisFrame);
            }
        }
    }

    if (joystickEnabled && sf::Joystick::isConnected(0))
    {
        for (const auto& inputEventInfo : Input::pressedJoystickButtonsThisFrame)
        {
            sf::Vector2f position(sf::Joystick::getAxisPosition(0, sf::Joystick::X),
                                  sf::Joystick::getAxisPosition(0, sf::Joystick::Y));

            std::string id = GenerateID(InputType::Joystick, inputEventInfo.InputValue);
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
        for (const auto& inputEventInfo : Input::pressedMouseButtonsThisFrame)
        {
            std::string id = GenerateID(InputType::Mouse, inputEventInfo.InputValue);
            auto it = mouseDelegates.find(id);
            if (it != mouseDelegates.end())
            {
                it->second.delegate(position, Input::pressedMouseButtonsThisFrame);
            }
        }
    }

    if (touchEnabled)
    {
        for (const auto& inputEventInfo : Input::fingerIndicesThisFrame)
        {
            std::string id = GenerateID(InputType::Touch, inputEventInfo.InputValue);
            auto it = touchDelegates.find(id);
            sf::Vector2i position = sf::Touch::getPosition(inputEventInfo.InputValue);
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

    CheckAllInputValidity();
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

void Input::ClearIdCaches()
{
    keyboardIdCache.clear();
    joystickIdCache.clear();
    mouseIdCache.clear();
    touchIdCache.clear();
}

void Input::CheckAllInputValidity()
{
    CheckInputValidity(&pressedKeysThisFrame);
    CheckInputValidity(&pressedJoystickButtonsThisFrame);
    CheckInputValidity(&fingerIndicesThisFrame);
    CheckInputValidity(&pressedMouseButtonsThisFrame);
}

void Input::CheckInputValidity(std::vector<Input::InputEventInfo>* inputThisFrame)
{
    auto it = inputThisFrame->begin();
    while (it != inputThisFrame->end())
    {
        if (it->IsValid)
        {
            it->IsHeldDown = true;
            ++it;
        }
        else
        {
            it = inputThisFrame->erase(it);
        }
    }
}

void Input::HandlePressedEvent(Input::InputType type, int inputValue)
{
    std::vector<InputEventInfo>* inputThisFrame = nullptr;

    switch (type)
    {
        case InputType::Keyboard:
            inputThisFrame = &pressedKeysThisFrame;
            break;
        case InputType::Joystick:
            inputThisFrame = &pressedJoystickButtonsThisFrame;
            break;
        case InputType::Touch:
            inputThisFrame = &fingerIndicesThisFrame;
            break;
        case InputType::Mouse:
            inputThisFrame = &pressedMouseButtonsThisFrame;
            break;
    }

    // Find the input event in the vector
    auto it = std::find_if(inputThisFrame->begin(), inputThisFrame->end(),
                           [inputValue](const InputEventInfo& info) {return info.InputValue == inputValue;});
    if(it != inputThisFrame->end())
        return;

    inputThisFrame->push_back(InputEventInfo(inputValue, false, true));
}

void Input::HandleReleasedEvent(Input::InputType type, int inputValue)
{
    std::vector<InputEventInfo>* inputThisFrame = nullptr;

    switch (type)
    {
        case InputType::Keyboard:
            inputThisFrame = &pressedKeysThisFrame;
            break;
        case InputType::Joystick:
            inputThisFrame = &pressedJoystickButtonsThisFrame;
            break;
        case InputType::Touch:
            inputThisFrame = &fingerIndicesThisFrame;
            break;
        case InputType::Mouse:
            inputThisFrame = &pressedMouseButtonsThisFrame;
            break;
    }

    for (InputEventInfo& inputEventInfo : *inputThisFrame)
    {
        if(inputEventInfo.InputValue == static_cast<int>(inputValue))
        {
            inputEventInfo.IsValid = false;
            inputEventInfo.IsHeldDown = false;
        }
    }
}

std::string Input::GenerateID(InputType inputType, const int& input)
{
    std::string hash;
    switch(inputType)
    {
        case InputType::Keyboard:
            if(keyboardIdCache.find(input) != keyboardIdCache.end())
                return keyboardIdCache[input];
            hash = GetHash(inputType, input);
            keyboardIdCache[input] = hash;
            break;
        case InputType::Mouse:
            if(mouseIdCache.find(input) != mouseIdCache.end())
                return mouseIdCache[input];
            hash = GetHash(inputType, input);
            mouseIdCache[input] = hash;
            break;
        case InputType::Joystick:
            if(joystickIdCache.find(input) != joystickIdCache.end())
                return joystickIdCache[input];
            hash = GetHash(inputType, input);
            joystickIdCache[input] = hash;
            break;
        case InputType::Touch:
            if(touchIdCache.find(input) != touchIdCache.end())
                return touchIdCache[input];
            hash = GetHash(inputType, input);
            touchIdCache[input] = hash;
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

std::string Input::GetHash(InputType inputType, const int& input)
{
    // Serialize the input into a string
    std::string data = std::to_string(inputType) + std::to_string(input);

    // Use a hash function to generate a hash of the serialized data
    std::hash<std::string> hasher;
    size_t hashValue = hasher(data);

    // Convert hash value to a string
    return std::to_string(hashValue);
}

