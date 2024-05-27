//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Input.h"

std::unordered_map<int, Input::ActionDelegate> Input::actionDelegates;

void Input::HandleInput() // NOLINT(*-convert-member-functions-to-static)
{
    for (const auto& pair : actionDelegates)
    {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(pair.first)))
        {
            pair.second(); // Call the delegate function
        }
    }
}

void Input::ClearAll()
{
	actionDelegates.clear();
}

void Input::Unsubscribe(sf::Keyboard::Key key)
{
    auto keyInt = static_cast<int>(key);
    auto iter = actionDelegates.find(keyInt);
    if(iter != actionDelegates.end())
		actionDelegates.erase(iter);
}

void Input::Subscribe(sf::Keyboard::Key key, const ActionDelegate &delegate)
{
    auto keyInt = static_cast<int>(key);
	actionDelegates[keyInt] = delegate;
}
