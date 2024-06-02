//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef ALPHA_SQUADRON_GAMEMANAGER_H
#define ALPHA_SQUADRON_GAMEMANAGER_H


#include "Player.h"

class GameManager
{
public:
    GameManager();
    Player player;

    void WPressed(std::vector<Input::InputEventInfo> otherKeys);
    void SPressed(std::vector<Input::InputEventInfo> otherKeys);
    void APressed(std::vector<Input::InputEventInfo> otherKeys);
    void DPressed(std::vector<Input::InputEventInfo> otherKeys);
    void UpPressed(std::vector<Input::InputEventInfo> otherKeys);
    void DownPressed(std::vector<Input::InputEventInfo> otherKeys);
    void LeftPressed(std::vector<Input::InputEventInfo> otherKeys);
    void RightPressed(std::vector<Input::InputEventInfo> otherKeys);
private:
    void SetUpInput();

};


#endif //ALPHA_SQUADRON_GAMEMANAGER_H
