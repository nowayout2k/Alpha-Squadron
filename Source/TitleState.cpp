// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file TitleState.cpp
 * @brief Implements the TitleState class.
 *
 * This source file provides the implementation for the TitleState class,
 * including resource loading, rendering, text blinking effect, and input handling
 * to transition from the title screen to the menu state.
 */

#include "../Headers/TitleState.h"
#include "../Headers/Utility.h"
namespace AlphaSquadron
{
	TitleState::TitleState(Engine::StateStack& stack, State::Context context)
		: State(stack, context), m_showText(true), m_textEffectTime(0), m_backgroundSprite()
	{
		// Load and set up the background texture.
		m_backgroundSprite.setTexture(ResourceManager::loadResource(TextureId::MetalBg));
		auto winSize = sf::Vector2f(context.Window->getSize());
		auto viewSize = sf::Vector2f(context.Window->getView().getSize());
		auto bgSize =
			sf::Vector2f(m_backgroundSprite.getTexture()->getSize().x, m_backgroundSprite.getTexture()->getSize().y);
		m_backgroundSprite.setScale(winSize.x / bgSize.x, winSize.y / bgSize.y);

		// Set up the continue text.
		m_continueText.setFont(ResourceManager::loadResource(Engine::FontId::Arnold));
		m_continueText.setString("Press Any Key To Continue!");
		Engine::Utility::centerOrigin(m_continueText);
		m_continueText.setPosition(viewSize.x / 2.f, viewSize.y / 1.5f);

		// Set up the company logo.
		auto& logoTex = ResourceManager::loadResource(TextureId::CompanyLogo);
		logoTex.setSmooth(true);
		m_logoSprite.setTexture(logoTex);
		auto textureSize = m_logoSprite.getTexture()->getSize();
		Engine::Utility::centerOrigin(m_logoSprite);
		m_logoSprite.setPosition(viewSize.x / 2.f, viewSize.y / 3.f);
		sf::Vector2f scale = Engine::Utility::calculateScaleFromViewPercentage(viewSize,
			sf::Vector2f(textureSize.x, textureSize.y),
			sf::Vector2f(0.5f, 0.5f),
			true);
		m_logoSprite.setScale(scale);
	}

	bool TitleState::handleEvent(const sf::Event& event)
	{
		// On any key press, transition to the menu state.
		if (event.type == sf::Event::KeyPressed)
		{
			requestStackPop();
			requestStackPush(StateId::Menu);
		}
		return true;
	}

	bool TitleState::update(sf::Time deltaTime)
	{
		// Update the blinking effect for the continue text.
		m_textEffectTime += deltaTime.asSeconds();
		if (m_textEffectTime >= 0.5f)
		{
			m_showText = !m_showText;
			m_textEffectTime = 0;
		}
		return true;
	}

	void TitleState::render()
	{
		// Draw the background, logo, and continue text (if visible) on the window.
		getContext().Window->draw(m_backgroundSprite);
		getContext().Window->draw(m_logoSprite);
		if (m_showText)
			getContext().Window->draw(m_continueText);
	}
}