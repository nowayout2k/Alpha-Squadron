//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef SFMLTEMPLATE_INPUT_H
#define SFMLTEMPLATE_INPUT_H

#include <functional>
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

class Input
{
public:
    using ActionDelegate = std::function<void()>;

    void HandleInput();
    static void subscribe(const sf::Keyboard::Key key, const ActionDelegate& delegate);
    static void unsubscribe(const sf::Keyboard::Key key);
    void clearAll();

private:
    static std::unordered_map<int, ActionDelegate> actionDelegates;
};

#endif //SFMLTEMPLATE_INPUT_H
