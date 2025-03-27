// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/CanvasNode.h"
#include "../Headers/Engine.h"
#include <algorithm>

namespace AlphaSquadron
{

	CanvasNode::CanvasNode()
		: m_healthBarElement1(nullptr), m_healthBgElement1(nullptr), m_healthTextElement1(nullptr),
		m_healthBarElement2(nullptr), m_healthBgElement2(nullptr), m_healthTextElement2(nullptr),
		m_player1Health(0), m_player2Health(0)
	{
		// Create UI elements using unique pointers, then store raw pointers for manipulation.
		auto healthBarElementPtr1 = std::make_unique<Engine::GameSprite>(false, AlphaSquadron::TextureId::MetalBg);
		auto healthBgElementPtr1 = std::make_unique<Engine::GameSprite>(false, AlphaSquadron::TextureId::MetalBg);
		auto healthTextElementPtr1 = std::make_unique<Engine::GameText>(Engine::FontId::Arnold,
			"Health Player 1",
			18,
			sf::Color::Black,
			sf::Text::Style::Regular,
			sf::Vector2f());


		m_healthTextElement1 = healthTextElementPtr1.get();
		m_healthBgElement1 = healthBgElementPtr1.get();
		m_healthBarElement1 = healthBarElementPtr1.get();
		m_healthBarElement1->setColor(sf::Color::Green);

		m_player1Health = 100;

		attachNode(std::move(healthTextElementPtr1));
		attachNode(std::move(healthBgElementPtr1));
		attachNode(std::move(healthBarElementPtr1));

		auto healthBarElementPtr2 = std::make_unique<Engine::GameSprite>(false, AlphaSquadron::TextureId::MetalBg);
		auto healthBgElementPtr2 = std::make_unique<Engine::GameSprite>(false, AlphaSquadron::TextureId::MetalBg);
		auto healthTextElementPtr2 = std::make_unique<Engine::GameText>(Engine::FontId::Arnold,
			"Health Player 2",
			18,
			sf::Color::Black,
			sf::Text::Style::Regular,
			sf::Vector2f());

		m_healthTextElement2 = healthTextElementPtr2.get();
		m_healthBgElement2 = healthBgElementPtr2.get();
		m_healthBarElement2 = healthBarElementPtr2.get();
		m_healthBarElement2->setColor(sf::Color::Green);

		m_player2Health = 100;

		// Attach UI elements to the node.
		attachNode(std::move(healthTextElementPtr2));
		attachNode(std::move(healthBgElementPtr2));
		attachNode(std::move(healthBarElementPtr2));
	}

	void CanvasNode::addPlayer2Ui()
	{
		m_healthTextElement2->setAlpha(255);
		m_healthBgElement2->setAlpha(255);
		m_healthBarElement2->setAlpha(255);
	}

	sf::FloatRect CanvasNode::getBoundingRect() const
	{
		sf::Vector2f viewSize = AlphaSquadron::World::getWorldView().getSize();
		return { 0.f, 0.f, viewSize.x, viewSize.y };
	}

	sf::FloatRect CanvasNode::getLocalBounds() const
	{
		return getBoundingRect();
	}

	void CanvasNode::update(sf::Time deltaTime, Engine::CommandQueue& commands)
	{
		auto view = AlphaSquadron::World::getWorldView();
		sf::Vector2f viewSize = view.getSize();
		sf::Vector2f viewCenter = view.getCenter();

		setOrigin(0, 0);
		setPosition(viewCenter - viewSize / 2.f);

		// Update health bar scale based on current player health and view size.
		sf::Vector2f bgSize(static_cast<float>(m_healthBgElement1->getTexture()->getSize().x),
			static_cast<float>(m_healthBgElement1->getTexture()->getSize().y));
		float scaleFactor = (viewSize.x / bgSize.x * 0.2f) * (m_player1Health / 100.f);
		m_healthBarElement1->setScale(scaleFactor, m_healthBarElement1->getScale().y);

		if(m_healthBarElement2->getScale().x != 0)
		{
			// Update health bar scale based on current player health and view size.
			sf::Vector2f bgSize(static_cast<float>(m_healthBgElement2->getTexture()->getSize().x),
				static_cast<float>(m_healthBgElement2->getTexture()->getSize().y));
			scaleFactor = (viewSize.x / bgSize.x * 0.2f) * (m_player2Health / 100.f);
			m_healthBarElement2->setScale(scaleFactor, m_healthBarElement2->getScale().y);
		}

	}

	void CanvasNode::render(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(*m_healthBgElement1, states);
		target.draw(*m_healthBarElement1, states);

		if(m_healthBarElement2 != nullptr)
		{
			target.draw(*m_healthBgElement2, states);
			target.draw(*m_healthBarElement2, states);
		}
	}

	unsigned int CanvasNode::getNodeType() const
	{
		return WorldNode::getNodeType() | static_cast<unsigned int>(AlphaSquadron::NodeType::UiCanvas);
	}

	void CanvasNode::loadResources()
	{
		m_healthBgElement1->loadResources();
		m_healthBarElement1->loadResources();
		m_healthTextElement1->loadResources();

		sf::Vector2f bgSize1(static_cast<float>(m_healthBgElement1->getTexture()->getSize().x),
			static_cast<float>(m_healthBgElement1->getTexture()->getSize().y));
		sf::Vector2f viewSize = AlphaSquadron::World::getWorldView().getSize();

		sf::Vector2f textureScaleAdjustment1(viewSize.x / bgSize1.x, viewSize.x / bgSize1.x);
		m_healthBgElement1->setScale(textureScaleAdjustment1.x * 0.205f, textureScaleAdjustment1.y * 0.015f);
		m_healthBarElement1->setScale(textureScaleAdjustment1.x * 0.2f, textureScaleAdjustment1.y * 0.01f);

		m_healthBgElement1->setPosition(0,viewSize.y * 0.02f);
		m_healthBarElement1->setPosition(viewSize.x * 0.001f,viewSize.y * 0.023f);

		m_healthTextElement1->setOrigin(-(m_healthBarElement1->getBoundingRect().width/2 - m_healthTextElement1->getBoundingRect().width), 0);
		m_healthTextElement1->setPosition(0, 0);

		m_healthBgElement2->loadResources();
		m_healthBarElement2->loadResources();
		m_healthTextElement2->loadResources();

		sf::Vector2f bgSize2(static_cast<float>(m_healthBgElement2->getTexture()->getSize().x),static_cast<float>(m_healthBgElement2->getTexture()->getSize().y));

		sf::Vector2f textureScaleAdjustment2(viewSize.x / bgSize2.x, viewSize.x / bgSize2.x);
		m_healthBgElement2->setScale(textureScaleAdjustment2.x * 0.205f, textureScaleAdjustment2.y * 0.015f);
		m_healthBarElement2->setScale(textureScaleAdjustment2.x * 0.2f, textureScaleAdjustment2.y * 0.01f);

		m_healthBgElement2->setPosition(viewSize.x - m_healthBgElement2->getBoundingRect().width,viewSize.y * 0.02f);
		m_healthBarElement2->setPosition(viewSize.x * 0.001f + (viewSize.x - m_healthBarElement2->getBoundingRect().width),viewSize.y * 0.023f);

		m_healthTextElement2->setOrigin(-(viewSize.x- m_healthBarElement2->getBoundingRect().width/2 - m_healthTextElement2->getBoundingRect().width), 0);
		m_healthTextElement2->setPosition(0,0);

		m_healthTextElement2->setAlpha(0);
		m_healthBgElement2->setAlpha(0);
		m_healthBarElement2->setAlpha(0);
	}

	void CanvasNode::setHeath(float health, bool isPlayer1)
	{
		isPlayer1 ? m_player1Health = std::max(health, 0.f) : m_player2Health = std::max(health, 0.f);
	}
}