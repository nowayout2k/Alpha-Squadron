//
// Created by Johnnie Otis on 10/13/24.
//

#include "SettingsState.h"
#include "Utility.h"
#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context) : State(stack, context), m_guiContainer()
{
	sf::Vector2f center = context.window->getView().getSize() / 2.f;
	m_backgroundSprite.setTexture(ResourceManager::loadResource(TextureId::Black));

	addButtonLabel(Player::AccelerateNegX, sf::Vector2f ( center.x, 100.f), "Move Left", context);
	addButtonLabel(Player::AcceleratePosX, sf::Vector2f ( center.x, 200.f), "Move Right", context);
	addButtonLabel(Player::AcceleratePosY, sf::Vector2f ( center.x, 300.f), "Move Up", context);
	addButtonLabel(Player::AccelerateNegY, sf::Vector2f ( center.x, 400.f), "Move Down", context);

	updateLabels();

	auto backButton = std::make_shared<GUI::Button>();
	backButton->setPosition(center.x, 500.f);
	backButton->setText(24, "Back");
	backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	m_guiContainer.pack(backButton);
}

void SettingsState::render(sf::RenderStates& states)
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(m_backgroundSprite, states);
	window.draw(m_guiContainer, states);
}

bool SettingsState::update(float deltaTime)
{
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;

	for (std::size_t actionType = 0; actionType < Player::ActionCount; ++actionType)
	{
		if (m_bindingButtons[actionType]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().input->assignKey(static_cast<Player::ActionType>(actionType), event.key.code);
				m_bindingButtons[actionType]->deactivate();
			}
			break;
		}
	}

	if (isKeyBinding)
		updateLabels();
	else
		m_guiContainer.handleEvent(event);

	return false;
}

void SettingsState::updateLabels()
{
	Player& input = *getContext().input;

	for (std::size_t i = 0; i < Player::ActionCount; ++i)
	{
		sf::Keyboard::Key key = input.getAssignedKey(static_cast<Player::ActionType>(i));
		m_bindingLabels[i]->setText(50, Utility::keyToString(key));
	}
}

void SettingsState::addButtonLabel(Player::ActionType actionType, sf::Vector2f offset, const std::string& text, Context context)
{
	m_bindingButtons[actionType] = std::make_shared<GUI::Button>();
	m_bindingButtons[actionType]->setPosition(offset.x, offset.y);
	m_bindingButtons[actionType]->setText(24, text);
	m_bindingButtons[actionType]->setToggle(true);

	m_bindingLabels[actionType] = std::make_shared<GUI::Label>("");
	m_bindingLabels[actionType]->setPosition(offset.x + 150.f, offset.y + 15.f);

	m_guiContainer.pack(m_bindingButtons[actionType]);
	m_guiContainer.pack(m_bindingLabels[actionType]);
}