//
// Created by Johnnie Otis on 6/2/24.
//

#ifndef SCROLLINGBACKGROUND_H_
#define SCROLLINGBACKGROUND_H_


#include "GameSprite.h"

 class ScrollingBackground : public Entity
{
public:
    explicit ScrollingBackground(std::vector<TextureId>&& textureTypes);
    void update(float deltaTime) override;
	void render(sf::RenderWindow& renderWindow, sf::RenderStates states) override;
	void collision(const Entity* other) override { return; }
	bool isColliding(const sf::Rect<float>& bounds) const override { return false; }
	sf::Rect<float> getGlobalBounds() override;
	void loadResources() override;
 private:
	sf::Texture* loadNextTexture();
	void swapCurrentTexture();
	std::vector<TextureId> m_textureTypes;
	int m_currentBackgroundIndex;
	sf::Vector2u m_windowSize;

	sf::Texture* m_textureA;
	sf::Texture* m_textureB;
	sf::Texture* m_currentTexture;

	std::unique_ptr<sf::Sprite> m_spriteA;
	std::unique_ptr<sf::Sprite> m_spriteB;
};


#endif //SCROLLINGBACKGROUND_H_
