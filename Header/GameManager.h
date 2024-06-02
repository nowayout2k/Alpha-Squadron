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
    void Update(float deltaTime);
    void Render(sf::RenderWindow& window);

private:
    void HandleCollisions();
    bool IsColliding(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
    std::vector<std::unique_ptr<Entity>> entities;
};


#endif //ALPHA_SQUADRON_GAMEMANAGER_H
