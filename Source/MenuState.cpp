// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include "../Headers/MenuState.h"
#include "../Headers/Button.h"
#include "../Headers/Audio.h"
#include "../Headers/ResourceManager.h"
#include "../Headers/Utility.h"

namespace AlphaSquadron
{
	MenuState::MenuState(Engine::StateStack& stack, Context context)
		: State(stack, context), m_backgroundSprite(), m_titleText(), m_guiContainer(*context.Audio)
	{
		sf::Vector2f center = context.Window->getView().getSize() / 2.f;

		// Set up background sprite.
		m_backgroundSprite.setTexture(ResourceManager::loadResource(TextureId::MetalBg));
		sf::Vector2f winSize(context.Window->getSize());
		sf::Vector2f bgSize(m_backgroundSprite.getTexture()->getSize());
		m_backgroundSprite.setScale(winSize.x / bgSize.x, winSize.y / bgSize.y);

		// Set up title text.
		m_titleText.setFont(ResourceManager::loadResource(Engine::FontId::Arnold));
		m_titleText.setString("Alpha Squadron");
		m_titleText.setCharacterSize(70);
		Engine::Utility::centerOrigin(m_titleText);
		m_titleText.setPosition(context.Window->getView().getSize().x / 2.f,
			context.Window->getView().getSize().y / 5.f);

		// Create Play button.
		auto localPlayButton = std::make_shared<Engine::Button>(context);
		localPlayButton->setPosition(center.x, center.y - 100);
		localPlayButton->setText(20, "Play");
		localPlayButton->setCallback([this]()
		{
		  requestStackPop();
		  requestStackPush(StateId::Game);
		});

		// Create Host Game button.
		auto hostMultiplayerButton = std::make_shared<Engine::Button>(context);
		hostMultiplayerButton->setPosition(center.x, center.y);
		hostMultiplayerButton->setText(20, "Host Game");
		hostMultiplayerButton->setCallback([this]()
		{
		  requestStackPop();
		  requestStackPush(StateId::HostGame);
		});

		// Create Join Game button.
		auto joinMultiplayerButton = std::make_shared<Engine::Button>(context);
		joinMultiplayerButton->setPosition(center.x, center.y + 100);
		joinMultiplayerButton->setText(20, "Join Game");
		joinMultiplayerButton->setCallback([this]()
		{
		  requestStackPop();
		  requestStackPush(StateId::JoinGame);
		});

		// Create Settings button.
		auto settingsButton = std::make_shared<Engine::Button>(context);
		settingsButton->setPosition(center.x, center.y + 200);
		settingsButton->setText(20, "Settings");
		settingsButton->setCallback([this]()
		{
		  requestStackPush(StateId::Settings);
		});

		// Create Exit button.
		auto exitButton = std::make_shared<Engine::Button>(context);
		exitButton->setPosition(center.x, center.y + 300);
		exitButton->setText(20, "Exit");
		exitButton->setCallback([this]()
		{
		  requestStackPop();
		});

		// Pack buttons into the GUI container.
		m_guiContainer.pack(localPlayButton);
		m_guiContainer.pack(hostMultiplayerButton);
		m_guiContainer.pack(joinMultiplayerButton);
		m_guiContainer.pack(settingsButton);
		m_guiContainer.pack(exitButton);

		// Play menu music.
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
}