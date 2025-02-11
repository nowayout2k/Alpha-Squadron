// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/UiCanvas.h"
#include "../Headers/Engine.h"

UiCanvas::UiCanvas() : m_health(0), m_healthBarElement(), m_healthBgElement(), m_healthTextElement()
{
	auto healthBarElementPtr = std::make_unique<GameSprite>(false,TextureId::MetalBg);
	auto healthBgElementPtr = std::make_unique<GameSprite>(false, TextureId::MetalBg);
	auto healthTextElementPtr = std::make_unique<GameText>(FontId::Arnold, "Health", 18, sf::Color::Black, sf::Text::Style::Regular, sf::Vector2f());

	m_healthTextElement = healthTextElementPtr.get();
	m_healthBgElement = healthBgElementPtr.get();
	m_healthBarElement = healthBarElementPtr.get();
	m_healthBarElement->setColor(sf::Color::Green);

	attachNode(std::move(healthTextElementPtr));
	attachNode(std::move(healthBgElementPtr));
	attachNode(std::move(healthBarElementPtr));
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
	auto bgSize = sf::Vector2f(m_healthBgElement->getTexture()->getSize().x, m_healthBgElement->getTexture()->getSize().y);
	m_healthBarElement->setScale((viewSize.x / bgSize.x*.2)*(m_health/100.f), m_healthBarElement->getScale().y);
}

void UiCanvas::render(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_healthBgElement, states);
	target.draw(*m_healthBarElement, states);
}

unsigned int UiCanvas::getNodeType() const
{
	return WorldNode::getNodeType() | static_cast<unsigned int>(NodeType::UiCanvas);
}

void UiCanvas::loadResources()
{
	m_healthBgElement->loadResources();
	m_healthBarElement->loadResources();
	m_healthTextElement->loadResources();

	auto bgSize = sf::Vector2f(m_healthBgElement->getTexture()->getSize().x, m_healthBgElement->getTexture()->getSize().y);
	sf::Vector2f viewSize = World::getWorldView().getSize();
	
	auto textureScaleAdjustment = sf::Vector2f(viewSize.x / bgSize.x, viewSize.x / bgSize.x);
	m_healthBgElement->setScale(textureScaleAdjustment.x * .205f, textureScaleAdjustment.y * .015f);
	m_healthBarElement->setScale(textureScaleAdjustment.x * .2f, textureScaleAdjustment.y * .01f);

	auto offset = sf::Vector2f(viewSize.x / 2 - m_healthBgElement->getBoundingRect().width/2, viewSize.y - m_healthBgElement->getBoundingRect().height/2);
	m_healthBgElement->setPosition(viewSize.x / 2 - m_healthBgElement->getBoundingRect().width/2, viewSize.y * .02f);
	m_healthBarElement->setPosition(viewSize.x * .001f + (viewSize.x / 2 - m_healthBarElement->getBoundingRect().width/2), viewSize.y * .023f);

	m_healthTextElement->setPosition(viewSize.x / 2, 0);
	m_healthTextElement->setOrigin(m_healthTextElement->getBoundingRect().width/2,0);
}