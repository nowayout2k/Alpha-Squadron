// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/CanvasNode.h"
#include "../Headers/Engine.h"
#include <algorithm>

CanvasNode::CanvasNode()
	: m_healthBarElement(nullptr)
	, m_healthBgElement(nullptr)
	, m_healthTextElement(nullptr)
{
	// Create UI elements using unique pointers, then store raw pointers for manipulation.
	auto healthBarElementPtr = std::make_unique<GameSprite>(false, TextureId::MetalBg);
	auto healthBgElementPtr = std::make_unique<GameSprite>(false, TextureId::MetalBg);
	auto healthTextElementPtr = std::make_unique<GameText>(FontId::Arnold, "Health", 18, sf::Color::Black, sf::Text::Style::Regular, sf::Vector2f());

	m_healthTextElement = healthTextElementPtr.get();
	m_healthBgElement = healthBgElementPtr.get();
	m_healthBarElement = healthBarElementPtr.get();
	m_healthBarElement->setColor(sf::Color::Green);

	m_playerHealths.push_back(100);

	// Attach UI elements to the node.
	attachNode(std::move(healthTextElementPtr));
	attachNode(std::move(healthBgElementPtr));
	attachNode(std::move(healthBarElementPtr));
}

sf::FloatRect CanvasNode::getBoundingRect() const
{
	sf::Vector2f viewSize = World::getWorldView().getSize();
	return { 0.f, 0.f, viewSize.x, viewSize.y };
}

sf::FloatRect CanvasNode::getLocalBounds() const
{
	return getBoundingRect();
}

void CanvasNode::update(sf::Time deltaTime, CommandQueue& commands)
{
	auto view = World::getWorldView();
	sf::Vector2f viewSize = view.getSize();
	sf::Vector2f viewCenter = view.getCenter();

	setOrigin(0, 0);
	setPosition(viewCenter - viewSize / 2.f);

	// Update health bar scale based on current player health and view size.
	sf::Vector2f bgSize(static_cast<float>(m_healthBgElement->getTexture()->getSize().x),
		static_cast<float>(m_healthBgElement->getTexture()->getSize().y));
	float scaleFactor = (viewSize.x / bgSize.x * 0.2f) * (m_playerHealths[0] / 100.f);
	m_healthBarElement->setScale(scaleFactor, m_healthBarElement->getScale().y);
}

void CanvasNode::render(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_healthBgElement, states);
	target.draw(*m_healthBarElement, states);
}

unsigned int CanvasNode::getNodeType() const
{
	return WorldNode::getNodeType() | static_cast<unsigned int>(NodeType::UiCanvas);
}

void CanvasNode::loadResources()
{
	m_healthBgElement->loadResources();
	m_healthBarElement->loadResources();
	m_healthTextElement->loadResources();

	sf::Vector2f bgSize(static_cast<float>(m_healthBgElement->getTexture()->getSize().x),
		static_cast<float>(m_healthBgElement->getTexture()->getSize().y));
	sf::Vector2f viewSize = World::getWorldView().getSize();

	sf::Vector2f textureScaleAdjustment(viewSize.x / bgSize.x, viewSize.x / bgSize.x);
	m_healthBgElement->setScale(textureScaleAdjustment.x * 0.205f, textureScaleAdjustment.y * 0.015f);
	m_healthBarElement->setScale(textureScaleAdjustment.x * 0.2f, textureScaleAdjustment.y * 0.01f);

	m_healthBgElement->setPosition(viewSize.x / 2 - m_healthBgElement->getBoundingRect().width / 2, viewSize.y * 0.02f);
	m_healthBarElement->setPosition(viewSize.x * 0.001f + (viewSize.x / 2 - m_healthBarElement->getBoundingRect().width / 2), viewSize.y * 0.023f);

	m_healthTextElement->setPosition(viewSize.x / 2, 0);
	m_healthTextElement->setOrigin(m_healthTextElement->getBoundingRect().width / 2, 0);
}

void CanvasNode::setHeath(float health, int playerNum)
{
	if (m_playerHealths.size() <= static_cast<size_t>(playerNum))
		return;

	m_playerHealths[playerNum] = std::max(health, 0.f);
}
