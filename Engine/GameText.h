//
// Created by Johnnie Otis on 6/10/24.
//

#ifndef GAMETEXT_H_
#define GAMETEXT_H_

#include <SFML/Graphics/Text.hpp>
#include "Entity.h"
#include "ResourceManager.h"
#include "Utility.h"

class GameText : public Entity
{
 public:
	GameText(FontId fontType, std::string text, unsigned int pixelSize, sf::Color color, sf::Text::Style style, sf::Vector2f position)
		: m_fontType(fontType), Entity(false)
	{
		setString(text);
		m_text.setCharacterSize(pixelSize);
		m_text.setFillColor(color);
		m_text.setStyle(style);
		m_text.setPosition(position);
		m_text.getGlobalBounds();
	}

	virtual unsigned int getNodeType() const override { return Entity::getNodeType() | (unsigned int)NodeType::Text; }

	virtual sf::Rect<float> getGlobalBounds() const override
	{
		sf::FloatRect bounds = m_text.getGlobalBounds();
		return getTransform().transformRect(bounds);
	}

	void setString(const std::string& text)
	{
		m_text.setString(text);
		Utility::centerOrigin(m_text);
	}

	virtual void update(float deltaTime) override { if(!isActive()) return; }

	virtual void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override
	{
		if(!isActive())
			return;
		renderTarget.draw(m_text, states);
	}

	void loadResources() override
	{
		m_text.setFont(ResourceManager::loadResource(m_fontType));
	};

	void collision(const Entity* other) override { if(!hasCollision()) return; }
	bool isColliding(const sf::Rect<float>& bounds) const override
	{
		if(!hasCollision())
			return false;

		return m_text.getGlobalBounds().intersects(bounds);
	}
 private:
	sf::Text m_text;
	FontId m_fontType;
};

#endif //GAMETEXT_H_
