// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef GAMESPRITE_H_
#define GAMESPRITE_H_

#include "ResourceManager.h"
#include "Utility.h"

class GameSprite : public WorldNode
{
public:
	explicit GameSprite(const bool hasCollision, const TextureId textureId, const bool centerOrigin = false,
		const sf::IntRect textureLoadArea = sf::IntRect(), const sf::IntRect spriteTextureRegion = sf::IntRect(), bool repeatTexture = false)
		: m_textureId(textureId), m_centerOrigin(centerOrigin), m_textureLoadArea(textureLoadArea), m_repeatTexture(repeatTexture),
			m_spriteTextureRegion(spriteTextureRegion), m_velocity(sf::Vector2f(0,0)), WorldNode(hasCollision)
		{}

	explicit GameSprite(const bool hasCollision, const bool centerOrigin = false,
		const sf::IntRect textureLoadArea = sf::IntRect(), const sf::IntRect spriteTextureRegion = sf::IntRect(), bool repeatTexture = false)
		: m_textureLoadArea(textureLoadArea), m_textureId(), m_centerOrigin(centerOrigin), m_repeatTexture(repeatTexture),
			m_spriteTextureRegion(spriteTextureRegion), m_velocity(sf::Vector2f(0,0)), WorldNode(hasCollision)
	{}

	~GameSprite() override = default;
	const sf::Texture* getTexture(){return m_sprite.getTexture();}
	void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
	void setVelocity(float x, float y) { m_velocity.x = x; m_velocity.y = y; }
	sf::Vector2f getVelocity() const { return m_velocity; }
	void update(sf::Time deltaTime, CommandQueue& commands) override { if(isActive()) {move(m_velocity * deltaTime.asSeconds());} }
	unsigned int getNodeType() const override { return WorldNode::getNodeType() | (unsigned int)NodeType::GameSprite; }
	sf::Rect<float> getLocalBounds() const { return m_sprite.getLocalBounds(); }
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;
	void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const;
	void loadResources() override;
	sf::FloatRect getBoundingRect() const override{return getWorldTransform().transformRect(m_sprite.getGlobalBounds());}
	void setSpriteOrigin(float x, float y){m_sprite.setOrigin(x,y);}
	void setColor(sf::Color color){m_sprite.setColor(color);}
	void setSpriteTextureRegion(sf::IntRect rect) { m_spriteTextureRegion = rect; m_sprite.setTextureRect(m_spriteTextureRegion); }
 protected:
	void setTextureId(TextureId textureId) { m_textureId = textureId; }
	void setTextureLoadArea(sf::IntRect rect) { m_textureLoadArea = rect; }

 private:
	sf::Sprite m_sprite;
	TextureId m_textureId;
	sf::IntRect m_textureLoadArea;
	sf::IntRect m_spriteTextureRegion;
	bool m_repeatTexture;
	bool m_centerOrigin;
	sf::Vector2f m_velocity;
 };

#endif //GAMESPRITE_H_
