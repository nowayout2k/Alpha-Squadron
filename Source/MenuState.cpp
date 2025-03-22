// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/MenuState.h"
#include "../Headers/Button.h"
#include "../Headers/Audio.h"

MenuState::MenuState(StateStack& stack, State::Context context) : State(stack, context),
		m_backgroundSprite(), m_titleText(), m_guiContainer()
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
	m_titleText.setPosition(context.Window->getView().getSize().x / 2.f, context.Window->getView().getSize().y / 5.f);

	auto localPlayButton = std::make_shared<GUI::Button>(context);
	localPlayButton->setPosition(center.x, center.y-100);
	localPlayButton->setText(20, "Play");
	localPlayButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(StateId::Game);
	});

	auto hostMultiplayerButton = std::make_shared<GUI::Button>(context);
	hostMultiplayerButton->setPosition(center.x, center.y);
	hostMultiplayerButton->setText(20, "Host Game");
	hostMultiplayerButton->setCallback([this] ()
	{
	  requestStackPop();
	  requestStackPush(StateId::HostGame);
	});

	auto joinMultiplayerButton = std::make_shared<GUI::Button>(context);
	joinMultiplayerButton->setPosition(center.x, center.y+100);
	joinMultiplayerButton->setText(20, "Join Game");
	joinMultiplayerButton->setCallback([this] ()
	{
	  requestStackPop();
	  requestStackPush(StateId::JoinGame);
	});

	auto settingsButton = std::make_shared<GUI::Button>(context);
	settingsButton->setPosition(center.x, center.y+200);
	settingsButton->setText(20, "Settings");
	settingsButton->setCallback([this] ()
	{
		requestStackPush(StateId::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(center.x, center.y+300);
	exitButton->setText(20, "Exit");
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	m_guiContainer.pack(localPlayButton);
	m_guiContainer.pack(hostMultiplayerButton);
	m_guiContainer.pack(joinMultiplayerButton);
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
