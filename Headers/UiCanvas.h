// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON__UI_H_
#define ALPHA_SQUADRON__UI_H_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "WorldNode.h"

class UiCanvas : public WorldNode
{
 protected:
	void render(sf::RenderTarget& target, sf::RenderStates states) const override;
 public:
	explicit UiCanvas();
	void updateHeath(float increment);
	sf::FloatRect getBoundingRect() const override;
	unsigned int getNodeType() const override;
	sf::FloatRect getLocalBounds() const;
	void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const;
	void update(sf::Time deltaTime, CommandQueue& commands) override;
 protected:
	void loadResources() override;

 private:
	float m_health;
	sf::Sprite m_healthBg;
	sf::Sprite m_healthBar;
};

#endif //ALPHA_SQUADRON__UI_H_
