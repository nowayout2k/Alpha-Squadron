//
// Created by Johnnie Otis on 5/30/24.
//

#ifndef ALPHA_SQUADRON_GAMEMANAGER_H
#define ALPHA_SQUADRON_GAMEMANAGER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "SpriteEntity.h"

class GameManager
{
public:
    GameManager();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    void handleCollisions();
    std::vector<std::unique_ptr<Entity>> m_entities;
};


#endif //ALPHA_SQUADRON_GAMEMANAGER_H
