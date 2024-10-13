//
// Created by Johnnie Otis on 10/12/24.
//

#include "MenuState.h"
#include "Utility.h"

MenuState::MenuState(StateStack& stack, State::Context context) : State(stack, context), m_backgroundSprite(ResourceManager::loadResource(TextureId::DecayedBuildings3))
{
	sf::Vector2f center = context.window->getView().getSize() / 2.f;

	sf::Text playOption;
	playOption.setFont(ResourceManager::loadResource(FontId::Gamer));
	playOption.setString("Play");
	Utility::centerOrigin(playOption);
	playOption.setPosition(center);

	sf::Text exitOption;
	exitOption.setFont(ResourceManager::loadResource(FontId::Gamer));
	exitOption.setString("Exit");
	Utility::centerOrigin(exitOption);
	exitOption.setPosition(sf::Vector2f(center.x,center.y+30));

	m_options.push_back(playOption);
	m_options.push_back(exitOption);
}

void MenuState::updateOptionText()
{
	if (m_options.empty())
		return;

	for(sf::Text& text : m_options)
	{
		text.setFillColor(sf::Color::White);
	}
	m_options[m_optionIndex].setFillColor(sf::Color::Red);
}
bool MenuState::handleEvent(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Up)
	{
		if (m_optionIndex > 0)
			m_optionIndex--;
		else
			m_optionIndex = m_options.size() - 1;
		updateOptionText();
	}
	else if (event.key.code == sf::Keyboard::Down)
	{
		if (m_optionIndex < m_options.size() - 1)
			m_optionIndex++;
		else
			m_optionIndex = 0;

		updateOptionText();
	}

	if (event.key.code == sf::Keyboard::Return)
	{
		if (m_optionIndex == Play)
		{
			requestStackPop();
			requestStackPush(Game);
		}
		else if (m_optionIndex == Exit)
		{
			requestStackPop();
		}
	}
	return true;
}
void MenuState::render()
{
	getContext().window->draw(m_backgroundSprite);
	for(auto& text : m_options)
		getContext().window->draw(text);
}
bool MenuState::update(float deltaTime)
{
	return true;
}
