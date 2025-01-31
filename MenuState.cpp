//
// Created by Johnnie Otis on 10/12/24.
//

#include "MenuState.h"
#include "Button.h"

MenuState::MenuState(StateStack& stack, State::Context context) : State(stack, context), m_backgroundSprite(ResourceManager::loadResource(TextureId::Black))
{
	sf::Vector2f center = context.window->getView().getSize() / 2.f;

	auto playButton = std::make_shared<GUI::Button>();
	playButton->setPosition(center.x, center.y);
	playButton->setText(24, "Play");
	playButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(StateId::Game);
	});

	auto settingsButton = std::make_shared<GUI::Button>();
	settingsButton->setPosition(center.x, center.y+100);
	settingsButton->setText(24, "Settings");
	settingsButton->setCallback([this] ()
	{
		requestStackPush(StateId::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>();
	exitButton->setPosition(center.x, center.y+200);
	exitButton->setText(24, "Exit");
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	m_guiContainer.pack(playButton);
	m_guiContainer.pack(settingsButton);
	m_guiContainer.pack(exitButton);
}

bool MenuState::handleEvent(const sf::Event& event)
{
	m_guiContainer.handleEvent(event);
	return true;
}
void MenuState::render(sf::RenderStates& states)
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());
	window.draw(m_backgroundSprite, states);
	window.draw(m_guiContainer, states);
}
bool MenuState::update(float deltaTime)
{
	return true;
}
