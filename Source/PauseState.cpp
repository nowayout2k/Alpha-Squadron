// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/PauseState.h"
#include "../Headers/Button.h"

PauseState::PauseState(StateStack& stack, Context context, bool letUpdatesThrough)
	: State(stack, context)
	, m_backgroundSprite()
	, m_pausedText()
	, m_guiContainer()
	, m_letUpdatesThrough(letUpdatesThrough)
{
	sf::Font& font = ResourceManager::loadResource(FontId::Arnold);
	sf::Vector2f windowSize(context.Window->getSize());

	m_pausedText.setFont(font);
	m_pausedText.setString("Game Paused");
	m_pausedText.setCharacterSize(70);
	Utility::centerOrigin(m_pausedText);
	m_pausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	auto returnButton = std::make_shared<GUI::Button>(context);
	returnButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
	returnButton->setText(40, "Return");
	returnButton->setCallback([this] ()
	{
	  requestStackPop();
	});

	auto backToMenuButton = std::make_shared<GUI::Button>(context);
	backToMenuButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
	backToMenuButton->setText(40, "Back to menu");
	backToMenuButton->setCallback([this] ()
	{
	  requestStateClear();
	  requestStackPush(StateId::Menu);
	});

	m_guiContainer.pack(returnButton);
	m_guiContainer.pack(backToMenuButton);

	getContext().Audio->pauseMusic(true);
}

PauseState::~PauseState()
{
	getContext().Audio->pauseMusic(false);
}

void PauseState::render()
{
	sf::RenderWindow& window = *getContext().Window;
	window.setView(window.getDefaultView());
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(sf::Vector2f(window.getSize()));
	window.draw(backgroundShape);
	window.draw(m_pausedText);
	window.draw(m_instructionText);
	window.draw(m_guiContainer);
}
bool PauseState::update(sf::Time deltaTime)
{
	return m_letUpdatesThrough;
}
bool PauseState::handleEvent(const sf::Event& event)
{
	m_guiContainer.handleEvent(event);
	return false;
}
