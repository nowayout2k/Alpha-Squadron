//
// Created by Johnnie Otis on 6/2/24.
//

#ifndef ALPHA_SQUADRON_HEADER_SCROLLINGBACKGROUND_H_
#define ALPHA_SQUADRON_HEADER_SCROLLINGBACKGROUND_H_


#include "GameSprite.h"

 class ScrollingBackground : public Entity
{
public:
    explicit ScrollingBackground(std::vector<std::string>&& backgroundTexturePaths);
    void update(float deltaTime) override;
	void render(sf::RenderWindow& renderWindow, sf::RenderStates states) override;
	void collision(const Entity* other) override { return; }
	bool isColliding(const sf::Rect<float>& bounds) const override { return false; }
	sf::Rect<float> getGlobalBounds() override;
 private:
	std::shared_ptr<sf::Texture> loadNextTexture();
	void swapCurrentTexture();
	std::vector<std::string> m_backgroundPaths;
	int m_currentBackgroundIndex;
	sf::Vector2u m_windowSize;

	std::shared_ptr<sf::Texture> m_textureA;
	std::shared_ptr<sf::Texture> m_textureB;
	std::shared_ptr<sf::Texture> m_currentTexture;

	std::unique_ptr<sf::Sprite> m_spriteA;
	std::unique_ptr<sf::Sprite> m_spriteB;
};


#endif //ALPHA_SQUADRON_HEADER_SCROLLINGBACKGROUND_H_
