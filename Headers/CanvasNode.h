// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON__UI_H_
#define ALPHA_SQUADRON__UI_H_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "WorldNode.h"
#include "GameSprite.h"
#include "GameText.h"

class CanvasNode : public WorldNode
{
 protected:
	void render(sf::RenderTarget& target, sf::RenderStates states) const override;
 public:
	explicit CanvasNode();
	sf::FloatRect getBoundingRect() const override;
	unsigned int getNodeType() const override;
	sf::FloatRect getLocalBounds() const;
	void update(sf::Time deltaTime, CommandQueue& commands) override;
	void setHeath(float health, int playerNum);
 protected:
	void loadResources() override;
 private:
	std::vector<float> m_playerHealths;
	GameSprite* m_healthBgElement;
	GameSprite* m_healthBarElement;
	GameText* m_healthTextElement;
};

#endif //ALPHA_SQUADRON__UI_H_
