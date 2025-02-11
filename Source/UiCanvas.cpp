// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/UiCanvas.h"
#include "../Headers/Engine.h"

UiCanvas::UiCanvas() : m_health(0), m_healthBar(), m_healthBg()
{
}

sf::FloatRect UiCanvas::getBoundingRect() const
{
	sf::Vector2f viewSize = World::getWorldView().getSize();
	return {0.f, 0.f, viewSize.x, viewSize.y};
}

sf::FloatRect UiCanvas::getLocalBounds() const
{
	return getBoundingRect();
}

void UiCanvas::update(sf::Time deltaTime, CommandQueue& commands)
{
	auto view = World::getWorldView();
	sf::Vector2f viewSize = view.getSize();
	sf::Vector2f viewCenter = view.getCenter();

	setOrigin(0, 0);
	setPosition(viewCenter - viewSize / 2.f);
	auto bgSize = sf::Vector2f(m_healthBg.getTexture()->getSize().x, m_healthBg.getTexture()->getSize().y);
	m_healthBar.setScale((viewSize.x / bgSize.x*.2)*(m_health/100.f), m_healthBar.getScale().y);
}

void UiCanvas::render(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_healthBg, states);
	target.draw(m_healthBar, states);
}

unsigned int UiCanvas::getNodeType() const
{
	return WorldNode::getNodeType() | static_cast<unsigned int>(NodeType::UiCanvas);
}

void UiCanvas::loadResources()
{
	m_healthBg.setTexture(ResourceManager::loadResource(TextureId::MetalBg));
	m_healthBar.setTexture(ResourceManager::loadResource(TextureId::MetalBg));

	sf::Vector2f viewSize = World::getWorldView().getSize();
	auto bgSize = sf::Vector2f(m_healthBg.getTexture()->getSize().x, m_healthBg.getTexture()->getSize().y);

	auto textureScaleAdjustment = sf::Vector2f(viewSize.x / bgSize.x, viewSize.x / bgSize.x);

	m_healthBg.setScale(textureScaleAdjustment.x * .2f, textureScaleAdjustment.y * .012f);
	m_healthBar.setScale(textureScaleAdjustment.x * .2f, textureScaleAdjustment.y * .01f);
	m_healthBar.setColor(sf::Color::Green);

	auto offset = sf::Vector2f(viewSize.x / 2 - m_healthBg.getGlobalBounds().width/2, viewSize.y * .015f - m_healthBg.getGlobalBounds().height/2);
	m_healthBg.setPosition(0.f + offset.x, 0.f + offset.y);
	m_healthBar.setPosition(viewSize.x * .001f + offset.x, viewSize.y * .001f + offset.y);
}