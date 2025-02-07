// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Animation.h"
void Animation::update(sf::Time dt)
{
	sf::Time timePerFrame = m_duration / static_cast<float>(m_numFrames);
	m_elapsedTime += dt;
	sf::Vector2i textureBounds(m_sprite.getTexture()->getSize());
	sf::IntRect textureRect = m_sprite.getTextureRect();
	if (m_currentFrame == 0)
		textureRect = sf::IntRect(0, 0, m_frameSize.x, m_frameSize.y);
	while (m_elapsedTime >= timePerFrame && (m_currentFrame <= m_numFrames || m_repeat))
	{
		textureRect.left += textureRect.width;
		if (textureRect.left + textureRect.width > textureBounds.x)
		{
			textureRect.left = 0;
			textureRect.top += textureRect.height;
		}

		m_elapsedTime -= timePerFrame;
		if (m_repeat)
		{
			m_currentFrame = (m_currentFrame + 1) % m_numFrames;
			if (m_currentFrame == 0)
				textureRect = sf::IntRect(0, 0, m_frameSize.x,m_frameSize.y);
		}
		else
		{
			m_currentFrame++;
		}
	}
	m_sprite.setTextureRect(textureRect);
}
void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
}
