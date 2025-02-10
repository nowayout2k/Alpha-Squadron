// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/UiCanvas.h"
#include "../Headers/Engine.h"

UiCanvas::UiCanvas() : m_health(0), m_healthBar(), m_healthBg()
{
	Utility::centerOrigin(m_healthBar);
	Utility::centerOrigin(m_healthBg);
	sf::Vector2f viewSize = Engine::getWindow().getView().getSize();
	m_healthBg.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
	m_healthBar.setPosition(viewSize.x / 2.f, viewSize.y / 2.f);
}

sf::FloatRect UiCanvas::getBoundingRect() const
{
	auto view = Engine::getWindow().getView();
	sf::Vector2f viewSize = view.getSize();
	sf::Vector2f viewPosition = view.getCenter() - viewSize / 2.f;
	return {viewPosition.x,viewPosition.y, viewSize.x, viewSize.y};
}

sf::FloatRect UiCanvas::getLocalBounds() const
{
	return getBoundingRect();
}

void UiCanvas::update(sf::Time deltaTime, CommandQueue& commands)
{
	auto view = Engine::getWindow().getView();
	sf::Vector2f viewSize = view.getSize();
	auto viewCenter = view.getCenter();
	auto newPos = viewCenter - viewSize / 2.f;
	setPosition(viewCenter.x,viewCenter.y);
}

void UiCanvas::render(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_healthBg, states);
	target.draw(m_healthBar, states);
	if(Debug::isCollidersVisible())
		drawBoundingRect(target, states);
}

void UiCanvas::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::FloatRect rect = getBoundingRect();

	sf::RectangleShape rectangleShape;
	rectangleShape.setPosition(sf::Vector2f(rect.left, rect.top));
	rectangleShape.setSize(sf::Vector2f(rect.width, rect.height));
	rectangleShape.setFillColor(sf::Color::Transparent);
	rectangleShape.setOutlineColor(sf::Color::Green);
	rectangleShape.setOutlineThickness(3.f);

	sf::CircleShape circleShape;
	circleShape.setPosition(getPosition().x + (getOrigin().x * rect.width), getPosition().y + (getOrigin().y * rect.height));
	circleShape.setRadius(1.f);
	circleShape.setFillColor(sf::Color::Red);
	circleShape.setOutlineColor(sf::Color::Red);
	circleShape.setOutlineThickness(3.f);

	target.draw(rectangleShape);
	target.draw(circleShape);
}

unsigned int UiCanvas::getNodeType() const
{
	return WorldNode::getNodeType() | static_cast<unsigned int>(NodeType::UiCanvas);
}

void UiCanvas::updateHeath(float increment)
{
	m_health += increment;
}

void UiCanvas::loadResources()
{
	m_healthBg.setTexture(ResourceManager::loadResource(TextureId::MetalBg));
	m_healthBar.setTexture(ResourceManager::loadResource(TextureId::MetalBg));
}
