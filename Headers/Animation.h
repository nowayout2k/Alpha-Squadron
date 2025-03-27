// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON_HEADERS_ANIMATION_H_
#define ALPHA_SQUADRON_HEADERS_ANIMATION_H_

#include "ResourceManager.h"

#include <SFML/Graphics.hpp>

/**
 * @file Animation.h
 * @brief Declaration of the Animation class.
 *
 * The Animation class is responsible for handling frame-based animations.
 * It inherits from sf::Drawable and sf::Transformable to support drawing and transformation.
 */
class Animation : public sf::Drawable, public sf::Transformable
{
 public:
	/**
	 * @brief Default constructor.
	 */
	explicit Animation() = default;

	/**
	 * @brief Constructs an Animation.
	 * @param texture The texture containing the animation frames.
	 * @param frameSize The size of each frame.
	 * @param numFrames The number of frames in the animation.
	 * @param duration The total duration of the animation.
	 */
	Animation(sf::Texture& texture, sf::Vector2i frameSize, std::size_t numFrames, sf::Time duration)
		: m_sprite(texture), m_frameSize(frameSize), m_numFrames(numFrames), m_duration(duration) {}

	/**
	 * @brief Updates the animation based on the elapsed time.
	 * @param deltaTime The time elapsed since the last update.
	 */
	void update(sf::Time deltaTime);

	/**
	 * @brief Draws the animation.
	 * @param target The render target.
	 * @param states The current render states.
	 */
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/**
	 * @brief Returns the local bounds of the sprite.
	 * @return A FloatRect representing the local bounds.
	 */
	sf::FloatRect getLocalBounds() { return m_sprite.getLocalBounds(); }

	/**
	 * @brief Checks if the animation is complete.
	 * @return True if the current frame is greater than or equal to the number of frames.
	 */
	bool isComplete() const { return m_currentFrame >= m_numFrames; }

	/**
	 * @brief Sets the texture for the animation.
	 * @param texture The texture to set.
	 */
	void setTexture(const sf::Texture& texture) { m_sprite.setTexture(texture); }

	/**
	 * @brief Retrieves the texture used by the animation.
	 * @return A pointer to the texture.
	 */
	const sf::Texture* getTexture() const { return m_sprite.getTexture(); }

	/**
	 * @brief Sets the size of each frame.
	 * @param frameSize The size of each frame.
	 */
	void setFrameSize(sf::Vector2i frameSize) { m_frameSize = frameSize; }

	/**
	 * @brief Retrieves the size of each frame.
	 * @return The frame size as a Vector2i.
	 */
	sf::Vector2i getFrameSize() const { return m_frameSize; }

	/**
	 * @brief Sets the number of frames in the animation.
	 * @param numFrames The number of frames.
	 */
	void setNumFrames(std::size_t numFrames) { m_numFrames = numFrames; }

	/**
	 * @brief Retrieves the number of frames in the animation.
	 * @return The number of frames.
	 */
	std::size_t getNumFrames() const { return m_numFrames; }

	/**
	 * @brief Sets the duration of the animation.
	 * @param duration The duration.
	 */
	void setDuration(sf::Time duration) { m_duration = duration; }

	/**
	 * @brief Retrieves the duration of the animation.
	 * @return The duration.
	 */
	sf::Time getDuration() const { return m_duration; }

	/**
	 * @brief Sets whether the animation should repeat.
	 * @param isRepeating True if the animation should repeat.
	 */
	void setRepeating(bool isRepeating) { m_repeat = isRepeating; }

	/**
	 * @brief Checks if the animation is set to repeat.
	 * @return True if repeating.
	 */
	bool isRepeating() const { return m_repeat; }

	/**
	 * @brief Restarts the animation.
	 */
	void restart() { m_currentFrame = 0; }

	/**
	 * @brief Returns the local bounds of the animation.
	 * @return A FloatRect representing the local bounds.
	 */
	sf::FloatRect getLocalBounds() const { return { getOrigin(), static_cast<sf::Vector2f>(getFrameSize()) }; }

	/**
	 * @brief Returns the global bounds of the animation.
	 * @return A FloatRect representing the global bounds.
	 */
	sf::FloatRect getGlobalBounds() const { return getTransform().transformRect(getLocalBounds()); }

 private:
	sf::Sprite m_sprite;             ///< Sprite used for displaying the animation.
	sf::Vector2i m_frameSize;        ///< Size of each animation frame.
	std::size_t m_numFrames{};       ///< Number of frames in the animation.
	std::size_t m_currentFrame{};    ///< Current frame index.
	sf::Time m_duration;             ///< Total duration of the animation.
	sf::Time m_elapsedTime;          ///< Elapsed time since the last frame update.
	bool m_repeat{};                 ///< Flag indicating whether the animation should repeat.
};

#endif // ALPHA_SQUADRON_HEADERS_ANIMATION_H_
