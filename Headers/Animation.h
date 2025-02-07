// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON_HEADERS_ANIMATION_H_
#define ALPHA_SQUADRON_HEADERS_ANIMATION_H_
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class Animation : public sf::Drawable, public sf::Transformable
{
 public:
	explicit Animation() = default;
	Animation(sf::Texture& texture, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration)
			: m_sprite(texture), m_frameSize(frameSize), m_numFrames(numFrames), m_duration(duration){};
	void update(sf::Time deltaTime);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect getLocalBounds() { return m_sprite.getLocalBounds(); }
	bool isComplete() const { return m_currentFrame >= m_numFrames; }
	void setTexture(const sf::Texture& texture) { m_sprite.setTexture(texture); }
	const sf::Texture* getTexture() const { return m_sprite.getTexture(); }
	void setFrameSize(sf::Vector2i frameSize) { m_frameSize = frameSize; }
	sf::Vector2i getFrameSize() const { return m_frameSize; }
	void setNumFrames(std::size_t numFrames) { m_numFrames = numFrames; }
	std::size_t getNumFrames() const { return m_numFrames; }
	void setDuration(sf::Time duration){ m_duration = duration; }
	sf::Time getDuration() const { return m_duration; }
	void setRepeating(bool isRepeating) { m_repeat = isRepeating; }
	bool isRepeating() const { return m_repeat; }
	void restart() { m_currentFrame = 0; }
	sf::FloatRect getLocalBounds() const { return { getOrigin(), static_cast<sf::Vector2f>(getFrameSize()) }; }
	sf::FloatRect getGlobalBounds() const { return getTransform().transformRect(getLocalBounds()); }

 private:
	sf::Sprite m_sprite;
	sf::Vector2i m_frameSize;
	std::size_t m_numFrames{};
	std::size_t m_currentFrame{};
	sf::Time m_duration;
	sf::Time m_elapsedTime;
	bool m_repeat{};
};

#endif //ALPHA_SQUADRON_HEADERS_ANIMATION_H_
