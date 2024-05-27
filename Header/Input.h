//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef SFML_CORE_HEADER_INPUT_H_
#define SFML_CORE_HEADER_INPUT_H_

#include <functional>
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

class Input
{
public:
    using ActionDelegate = std::function<void()>;

    void HandleInput();
    static void Subscribe(sf::Keyboard::Key key, const ActionDelegate& delegate);
    static void Unsubscribe(sf::Keyboard::Key key);
	static void ClearAll();

private:
    static std::unordered_map<int, ActionDelegate> actionDelegates;
};

#endif //SFML_CORE_HEADER_INPUT_H_
