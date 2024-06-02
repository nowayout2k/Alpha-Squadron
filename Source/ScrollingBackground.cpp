//
// Created by Johnnie Otis on 6/2/24.
//

#include "../Header/ScrollingBackground.h"

ScrollingBackground::ScrollingBackground() : SpriteEntity(false, "../Assets/Textures/Background.jpg")
{
    sf::Vector2u windowSize = WindowManager::GetSize();
    sf::Vector2u textureSize = m_texture.getSize();
    setScale(windowSize.x/textureSize.x, windowSize.y/textureSize.y);
    setPosition(0, 0);
}

void ScrollingBackground::Update(float deltaTime)
{

}
