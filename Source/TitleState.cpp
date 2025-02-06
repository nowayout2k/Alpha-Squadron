// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/TitleState.h"
#include "../Headers/Utility.h"

TitleState::TitleState(StateStack& stack, State::Context context) : State(stack, context), m_showText(true), m_textEffectTime(0), m_backgroundSprite()
{
	m_backgroundSprite.setTexture(ResourceManager::loadResource(TextureId::MetalBg));
	auto winSize = sf::Vector2f(context.window->getSize().x, context.window->getSize().y );
	auto bgSize = sf::Vector2f(m_backgroundSprite.getTexture()->getSize().x, m_backgroundSprite.getTexture()->getSize().y);
	m_backgroundSprite.setScale(winSize.x/bgSize.x, winSize.y/bgSize.y);
	m_continueText.setFont(ResourceManager::loadResource(FontId::Arnold));
	m_continueText.setString("Press Any Key To Continue!");
	Utility::centerOrigin(m_continueText);
	m_continueText.setPosition(context.window->getView().getSize().x/2.f, context.window->getView().getSize().y/1.5f);

	m_logoSprite.setTexture(ResourceManager::loadResource(TextureId::CompanyLogo));
	Utility::centerOrigin(m_logoSprite);
	m_logoSprite.setPosition(context.window->getView().getSize().x/2.f, context.window->getView().getSize().y / 3.f);
}

bool TitleState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(StateId::Menu);
	}
	return true;
}

bool TitleState::update(sf::Time deltaTime)
{
	m_textEffectTime += deltaTime.asSeconds();
	if (m_textEffectTime >= 0.5f)
	{
		m_showText = !m_showText;
		m_textEffectTime = 0;
	}
	return true;
}
void TitleState::render(sf::RenderStates& states)
{
	getContext().window->draw(m_backgroundSprite);

	getContext().window->draw(m_logoSprite);
	if(m_showText)
		getContext().window->draw(m_continueText);
}
