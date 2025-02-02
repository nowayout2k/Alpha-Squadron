// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/LoadingState.h"
#include "../Headers/ResourceManager.h"
#include "../Headers/Utility.h"

LoadingState::LoadingState(StateStack& stateStack, Context& context, std::function<void()> loadingTask) : State(stateStack, context)
{
	m_loadingText.setFont(ResourceManager::loadResource(FontId::Gamer));
	m_loadingText.setString("Loading Resources");
	Utility::centerOrigin(m_loadingText);
	m_loadingText.setPosition(getContext().window->getSize().x / 2u, getContext().window->getSize().y / 2u + 50);
	m_progressBarBackground.setFillColor(sf::Color::White);
	m_progressBarBackground.setSize(sf::Vector2f(getContext().window->getSize().x - 20,10));
	m_progressBarBackground.setPosition(10, m_loadingText.getPosition().y +40);
	m_progressBar.setFillColor(sf::Color(100,100,100));
	m_progressBar.setSize(sf::Vector2f(200, 10));
	m_progressBar.setPosition(10, m_loadingText.getPosition().y + 40);
	setCompletion(0.f);
	m_parallelTask.execute(loadingTask);
}

bool LoadingState::update(float deltaTime)
{
	if (m_parallelTask.isFinished())
	{
		requestStackPop();
		requestStackPush(StateId::Game);
	}
	else
	{
		setCompletion(m_parallelTask.getCompletion());
	}
	return true;
}

void LoadingState::setCompletion(float percent)
{
	if (percent > 1.f)
		percent = 1.f;
	m_progressBar.setSize(sf::Vector2f(m_progressBarBackground.getSize().x * percent,m_progressBar.getSize().y));
}

void LoadingState::render(sf::RenderStates& states)
{
	getContext().window->draw(m_loadingText, states);
	getContext().window->draw(m_progressBarBackground, states);
	getContext().window->draw(m_progressBar, states);
}

bool LoadingState::handleEvent(const sf::Event& event)
{
	return true;
}
