// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/SettingsState.h"
#include "../Headers/Utility.h"
#include <SFML/Graphics/RenderWindow.hpp>


SettingsState::SettingsState(StateStack& stack, Context context) : State(stack, context), m_guiContainer()
{

	m_backgroundSprite.setTexture(ResourceManager::loadResource(TextureId::MetalBg));
	auto winSize = sf::Vector2f(context.Window->getSize().x, context.Window->getSize().y);
	auto bgSize = sf::Vector2f(m_backgroundSprite.getTexture()->getSize().x, m_backgroundSprite.getTexture()->getSize().y);
	m_backgroundSprite.setScale(winSize.x/bgSize.x, winSize.y/bgSize.y);

	for (std::size_t x = 0; x < 2; ++x)
	{
		addButtonLabel(KeyBinding::ActionType::AccelerateNegX, sf::Vector2i (x, 0), "Move Left", context);
		addButtonLabel(KeyBinding::ActionType::AcceleratePosX, sf::Vector2i (x, 1), "Move Right", context);
		addButtonLabel(KeyBinding::ActionType::AcceleratePosY, sf::Vector2i (x, 2), "Move Up", context);
		addButtonLabel(KeyBinding::ActionType::AccelerateNegY, sf::Vector2i (x, 3), "Move Down", context);
		addButtonLabel(KeyBinding::ActionType::Fire, sf::Vector2i (x, 4), "Fire", context);
		addButtonLabel(KeyBinding::ActionType::LaunchMissile, sf::Vector2i (x, 5), "Launch Missile", context);
	}
	updateLabels();
	sf::Vector2f center = context.Window->getView().getSize() / 2.f;
	auto backButton = std::make_shared<GUI::Button>(context);

	backButton->setButtonOrigin(0,0);
	backButton->setPosition(0,0);
	backButton->setText(24, "Back");
	backButton->setCallback([this] { requestStackPop(); });

	m_guiContainer.pack(backButton);
}

void SettingsState::render()
{
	sf::RenderWindow& window = *getContext().Window;
	window.draw(m_backgroundSprite);
	window.draw(m_guiContainer);
}

bool SettingsState::update(sf::Time deltaTime)
{
	return true;
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;

	for (std::size_t i = 0; i < 2*KeyBinding::ActionType::ActionCount; ++i)
	{
		if (m_bindingButtons[i]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				// Player 1
				if (i < KeyBinding::ActionType::ActionCount)
					getContext().KeysPlayer1->assignKey(static_cast<KeyBinding::ActionType>(i), event.key.code);

					// Player 2
				else
					getContext().KeysPlayer2->assignKey(static_cast<KeyBinding::ActionType>(i - KeyBinding::ActionType::ActionCount), event.key.code);
			}

			m_bindingButtons[i]->deactivate();
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
	for (std::size_t i = 0; i < KeyBinding::ActionType::ActionCount; ++i)
	{
		auto action = static_cast<LocalPlayerAction::ActionType>(i);

		// Get keys of both players
		sf::Keyboard::Key key1 = getContext().KeysPlayer1->getAssignedKey(action);
		sf::Keyboard::Key key2 = getContext().KeysPlayer2->getAssignedKey(action);

		// Assign both key strings to labels
		m_bindingLabels[i]->setText(40, Utility::keyToString(key1));
		m_bindingLabels[i + LocalPlayerAction::ActionType::ActionCount]->setText(40, Utility::keyToString(key2));
	}
}

void SettingsState::addButtonLabel(std::size_t index, sf::Vector2i offset, const std::string& text, Context context)
{
	sf::Vector2f screenSize = context.Window->getView().getSize();

	index += Player::ActionType::ActionCount * offset.x;

	m_bindingButtons[index] = std::make_shared<GUI::Button>(context);
	m_bindingButtons[index]->setPosition(offset.x==0 ? screenSize.x*.4 : screenSize.x*.8, (index%Player::ActionType::ActionCount + 1.f)*screenSize.y*.14);
	m_bindingButtons[index]->setText(18, text);
	m_bindingButtons[index]->setToggle(true);

	m_bindingLabels[index] = std::make_shared<GUI::Label>("");
	m_bindingLabels[index]->setPosition(offset.x==0 ? screenSize.x*.2 : screenSize.x*.6, (index%Player::ActionType::ActionCount + 1.f)*screenSize.y*.14);

	m_guiContainer.pack(m_bindingButtons[index]);
	m_guiContainer.pack(m_bindingLabels[index]);
}
