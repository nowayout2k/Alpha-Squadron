// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/MenuState.h"
#include "../Headers/Button.h"
#include "../Headers/Audio.h"

MenuState::MenuState(StateStack& stack, State::Context context) : State(stack, context),
		m_backgroundSprite(), m_titleText(), m_guiContainer(context.Audio)
{
	sf::Vector2f center = context.Window->getView().getSize() / 2.f;
	m_backgroundSprite.setTexture(ResourceManager::loadResource(TextureId::MetalBg));
	auto winSize = sf::Vector2f(context.Window->getSize().x, context.Window->getSize().y);
	auto bgSize = sf::Vector2f(m_backgroundSprite.getTexture()->getSize().x, m_backgroundSprite.getTexture()->getSize().y);
	m_backgroundSprite.setScale(winSize.x/bgSize.x, winSize.y/bgSize.y);

	m_titleText.setFont(ResourceManager::loadResource(FontId::Arnold));
	m_titleText.setString("Alpha Squadron");
	m_titleText.setCharacterSize(70);
	Utility::centerOrigin(m_titleText);
	m_titleText.setPosition(context.Window->getView().getSize().x / 2.f, context.Window->getView().getSize().y / 3.f);

	auto playButton = std::make_shared<GUI::Button>(sf::IntRect(0,0,208,64),
		sf::IntRect(223,0,208,64),
		sf::IntRect(445,0,208,64));
	playButton->setPosition(center.x, center.y);
	playButton->setText(24, "Play");
	playButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(StateId::Game);
	});

	auto settingsButton = std::make_shared<GUI::Button>(sf::IntRect(0,0,208,64),
		sf::IntRect(223,0,208,64),
		sf::IntRect(445,0,208,64));
	settingsButton->setPosition(center.x, center.y+100);
	settingsButton->setText(24, "Settings");
	settingsButton->setCallback([this] ()
	{
		requestStackPush(StateId::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(sf::IntRect(0,0,208,64),
		sf::IntRect(223,0,208,64),
		sf::IntRect(445,0,208,64));
	exitButton->setPosition(center.x, center.y+200);
	exitButton->setText(24, "Exit");
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	m_guiContainer.pack(playButton);
	m_guiContainer.pack(settingsButton);
	m_guiContainer.pack(exitButton);
	context.Audio->playMusic(MusicId::MenuMusic, 12);
}

bool MenuState::handleEvent(const sf::Event& event)
{
	m_guiContainer.handleEvent(event);
	return true;
}
void MenuState::render()
{
	sf::RenderWindow& window = *getContext().Window;
	window.setView(window.getDefaultView());

	window.draw(m_backgroundSprite);
	window.draw(m_guiContainer);
	window.draw(m_titleText);
}
bool MenuState::update(sf::Time deltaTime)
{
	return true;
}
