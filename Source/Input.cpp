//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Input.h"

std::unordered_map<int, Input::ActionDelegate> Input::actionDelegates;

void Input::HandleInput()
{
    for (const auto& pair : actionDelegates)
    {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(pair.first)))
        {
            pair.second(); // Call the delegate function
        }
    }
}

void Input::clearAll()
{
    actionDelegates.clear();
}

void Input::unsubscribe(const sf::Keyboard::Key key)
{
    auto keyInt = static_cast<int>(key);
    auto iter = actionDelegates.find(keyInt);
    if(iter != actionDelegates.end())
        actionDelegates.erase(iter);
}

void Input::subscribe(const sf::Keyboard::Key key, const std::function<void()>& delegate)
{
    auto keyInt = static_cast<int>(key);
    actionDelegates[keyInt] = delegate;
}
