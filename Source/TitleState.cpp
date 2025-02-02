// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/TitleState.h"
#include "../Headers/Utility.h"

TitleState::TitleState(StateStack& stack, State::Context context) : State(stack, context),
						m_backgroundSprite(ResourceManager::loadResource(TextureId::Black))
{
	m_text.setFont(ResourceManager::loadResource(FontId::Gamer));
	m_text.setString("Press Any Key To Continue!");
	Utility::centerOrigin(m_text);
	m_text.setPosition(context.window->getView().getSize() / 2.f);
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

bool TitleState::update(float deltaTime)
{
	m_textEffectTime += deltaTime;
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
	if(m_showText)
		getContext().window->draw(m_text);
}
