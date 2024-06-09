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

	bool loadNextTexture(sf::Texture& texture);
	void swapCurrentTexture();
	std::vector<std::string> m_backgroundPaths;
	int m_currentBackgroundIndex;
	sf::Vector2u m_windowSize;

	sf::Texture m_textureA;
	sf::Texture m_textureB;
	sf::Texture* m_currentTexture;

	std::unique_ptr<sf::Sprite> m_spriteA;
	std::unique_ptr<sf::Sprite> m_spriteB;
};


#endif //ALPHA_SQUADRON_HEADER_SCROLLINGBACKGROUND_H_
