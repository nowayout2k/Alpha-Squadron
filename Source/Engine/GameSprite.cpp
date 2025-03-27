// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include "../../Headers/Engine/GameSprite.h"

namespace Engine
{
	void GameSprite::render(sf::RenderTarget& renderTarget, sf::RenderStates states) const
	{
		renderTarget.draw(m_sprite, states);
		if (Engine::Debug::isCollidersVisible())
			drawBoundingRect(renderTarget, states);
	}

	void GameSprite::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
	{
		sf::FloatRect rect = getBoundingRect();

		sf::RectangleShape rectangleShape;
		rectangleShape.setPosition(sf::Vector2f(rect.left, rect.top));
		rectangleShape.setSize(sf::Vector2f(rect.width, rect.height));
		rectangleShape.setFillColor(sf::Color::Transparent);
		rectangleShape.setOutlineColor(sf::Color::Green);
		rectangleShape.setOutlineThickness(3.f);

		sf::CircleShape circleShape;
		circleShape.setPosition(getPosition().x + (getOrigin().x * rect.width),
			getPosition().y + (getOrigin().y * rect.height));
		circleShape.setRadius(1.f);
		circleShape.setFillColor(sf::Color::Red);
		circleShape.setOutlineColor(sf::Color::Red);
		circleShape.setOutlineThickness(3.f);

		target.draw(rectangleShape);
		target.draw(circleShape);
	}

	void GameSprite::loadResources()
	{
		auto& tex = AlphaSquadron::ResourceManager::loadResource(m_textureId, m_textureLoadArea);
		tex.setRepeated(m_repeatTexture);
		m_sprite.setTexture(tex);
		if (m_spriteTextureRegion != sf::IntRect())
			m_sprite.setTextureRect(m_spriteTextureRegion);
		if (m_centerOrigin)
			Utility::centerOrigin(m_sprite);
	}
}