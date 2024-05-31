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
private:
    void SetUpInput();

};


#endif //ALPHA_SQUADRON_GAMEMANAGER_H
