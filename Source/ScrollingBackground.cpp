//
// Created by Johnnie Otis on 6/2/24.
//

#include "../Header/ScrollingBackground.h"
#include "../Header/Game.h"

ScrollingBackground::ScrollingBackground(std::vector<TextureId>&& textureTypes)
{
	m_textureTypes = std::move(textureTypes);
	m_currentBackgroundIndex = -1;
	m_windowSize = Game::getWindowSize();
}

void ScrollingBackground::update(float deltaTime)
{
	m_spriteA->move(sf::Vector2f(-100,0) * deltaTime);
	m_spriteB->move(sf::Vector2f(-100,0) * deltaTime);
	if((float)m_textureA->getSize().x * m_spriteA->getScale().x + m_spriteA->getPosition().x <= 0)
	{
		swapCurrentTexture();
		m_spriteA->setTexture(*m_currentTexture);
		swapCurrentTexture();
		m_currentTexture = loadNextTexture();
		m_spriteB->setTexture(*m_currentTexture);

		m_spriteA->setPosition(0,0);
		m_spriteB->setPosition((float)m_textureA->getSize().x * m_spriteA->getScale().x,0);
	}
}

void ScrollingBackground::swapCurrentTexture()
{
	if(m_currentTexture == m_textureA)
		m_currentTexture = m_textureB;
	else
		m_currentTexture = m_textureA;
}

sf::Texture* ScrollingBackground::loadNextTexture()
{
	m_currentBackgroundIndex++;
	if(m_currentBackgroundIndex >= m_textureTypes.size())
		m_currentBackgroundIndex = 0;

	return ResourceCache::getTexture(m_textureTypes[m_currentBackgroundIndex]);
}
void ScrollingBackground::render(sf::RenderWindow& renderWindow, sf::RenderStates states)
{
	if(isActive())
	{
		renderWindow.draw(*m_spriteA, states);
		renderWindow.draw(*m_spriteB, states);
	}
}
sf::Rect<float> ScrollingBackground::getGlobalBounds()
{
	auto rectA = m_spriteA->getGlobalBounds();
	auto rectB = m_spriteB->getGlobalBounds();
	return sf::Rect<float>(rectA.left+rectB.left,rectA.top+rectB.top,rectA.width+rectB.width,rectA.height+rectB.height);
}
void ScrollingBackground::loadResources()
{
	m_textureA = loadNextTexture();
	m_textureB = loadNextTexture();

	m_currentTexture = m_textureA;

	m_spriteA = std::make_unique<sf::Sprite>(*m_textureA);
	m_spriteB = std::make_unique<sf::Sprite>(*m_textureB);

	m_spriteA->setScale((float)m_windowSize.x/(float)m_textureA->getSize().x, (float)m_windowSize.y/(float)m_textureA->getSize().y);
	m_spriteB->setScale((float)m_windowSize.x/(float)m_textureB->getSize().x, (float)m_windowSize.y/(float)m_textureB->getSize().y);

	m_spriteA->setPosition(0,0);
	m_spriteB->setPosition((float)m_textureA->getSize().x * m_spriteA->getScale().x,0);
}
