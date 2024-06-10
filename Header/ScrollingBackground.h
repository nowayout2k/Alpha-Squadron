//
// Created by Johnnie Otis on 6/2/24.
//

#ifndef ALPHA_SQUADRON_HEADER_SCROLLINGBACKGROUND_H_
#define ALPHA_SQUADRON_HEADER_SCROLLINGBACKGROUND_H_


#include "SpriteEntity.h"
#include "DrawableEntity.h"

class ScrollingBackground : public DrawableEntity
{
public:
    explicit ScrollingBackground(std::vector<std::string>&& backgroundTexturePaths);
    void update(float deltaTime) override;
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
