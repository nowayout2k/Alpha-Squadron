//
// Created by Johnnie Otis on 6/2/24.
//

#include "../Header/ScrollingBackground.h"

ScrollingBackground::ScrollingBackground() : SpriteEntity(false, "../Assets/Textures/Background.jpg")
{
	m_windowSize = WindowManager::getSize();
	m_textureSize = m_texture.getSize();
    setScale((m_windowSize.x/m_textureSize.x)*2, m_windowSize.y/m_textureSize.y);
    setPosition(0, 0);
}

void ScrollingBackground::update(float deltaTime)
{
	move(sf::Vector2f(-100,0) * deltaTime);
	if(m_textureSize.x * getScale().x + getPosition().x <= m_windowSize.x)
		setPosition(0,0);
}
