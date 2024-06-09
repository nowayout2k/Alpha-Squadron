//
// Created by Johnnie Otis on 6/2/24.
//

#include "../Header/ScrollingBackground.h"

ScrollingBackground::ScrollingBackground(std::vector<std::string>&& backgroundTexturePaths)
{
	m_backgroundPaths = std::move(backgroundTexturePaths);
	m_currentBackgroundIndex = 0;
	m_windowSize = WindowManager::getSize();

	m_spriteA = std::make_unique<sf::Sprite>();
	m_spriteB = std::make_unique<sf::Sprite>();

	addDrawable(m_spriteA.get(), false);
	addDrawable(m_spriteB.get(), false);

	loadNextTextures();

	m_spriteA->setScale((float)m_windowSize.x/(float)m_textureA.getSize().x, (float)m_windowSize.y/(float)m_textureA.getSize().y);
	m_spriteB->setScale((float)m_windowSize.x/(float)m_textureB.getSize().x, (float)m_windowSize.y/(float)m_textureB.getSize().y);

	m_spriteA->setPosition(0,0);
	m_spriteB->setPosition((float)m_textureA.getSize().x * m_spriteA->getScale().x,0);
}

void ScrollingBackground::update(float deltaTime)
{
	m_spriteA->move(sf::Vector2f(-100,0) * deltaTime);
	m_spriteB->move(sf::Vector2f(-100,0) * deltaTime);
	if((float)m_textureA.getSize().x * m_spriteA->getScale().x + m_spriteA->getPosition().x <= 0)
	{
		loadNextTextures();
		m_spriteA->setPosition(0,0);
		m_spriteB->setPosition((float)m_textureA.getSize().x * m_spriteA->getScale().x,0);
	}
}

bool ScrollingBackground::loadNextTextures()
{

	if (!m_textureB.loadFromFile(m_backgroundPaths[m_currentBackgroundIndex]))
	{
		Logger::Log(LogType::Error, "Texture not found at: " + m_backgroundPaths[m_currentBackgroundIndex]);
		return false;
	}
	m_spriteB->setTexture(m_textureB);

	m_currentBackgroundIndex++;
	if(m_currentBackgroundIndex >= m_backgroundPaths.size())
		m_currentBackgroundIndex = 0;

	if (!m_textureA.loadFromFile(m_backgroundPaths[m_currentBackgroundIndex]))
	{
		Logger::Log(LogType::Error, "Texture not found at: " + m_backgroundPaths[m_currentBackgroundIndex]);
		return false;
	}
	m_spriteA->setTexture(m_textureA);
	return true;
}
