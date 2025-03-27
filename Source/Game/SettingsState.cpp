// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file SettingsState.cpp
 * @brief Implements the SettingsState class.
 *
 * This source file defines the behavior for the SettingsState class, including GUI layout,
 * key binding handling, and updating labels to display current key assignments.
 */

#include "../../Headers/Game/SettingsState.h"
#include "../../Headers/Engine/Utility.h"
#include <SFML/Graphics/RenderWindow.hpp>
namespace AlphaSquadron
{
	SettingsState::SettingsState(Engine::StateStack& stack, Context context)
		: State(stack, context), m_guiContainer(*context.Audio)
	{
		// Set the background sprite texture and scale it to match the window size.
		m_backgroundSprite.setTexture(ResourceManager::loadResource(TextureId::MetalBg));
		auto winSize = sf::Vector2f(context.Window->getSize().x, context.Window->getSize().y);
		auto bgSize =
			sf::Vector2f(m_backgroundSprite.getTexture()->getSize().x, m_backgroundSprite.getTexture()->getSize().y);
		m_backgroundSprite.setScale(winSize.x / bgSize.x, winSize.y / bgSize.y);

		// Create key binding buttons and labels for both players.
		for (std::size_t x = 0; x < 2; ++x)
		{
			// Each call creates a binding for a specific action with a given text label.
			addButtonLabel(Engine::KeyBinding::ActionType::AccelerateNegX, sf::Vector2i(x, 0), "Move Left", context);
			addButtonLabel(Engine::KeyBinding::ActionType::AcceleratePosX, sf::Vector2i(x, 1), "Move Right", context);
			addButtonLabel(Engine::KeyBinding::ActionType::AccelerateNegY, sf::Vector2i(x, 2), "Move Up", context);
			addButtonLabel(Engine::KeyBinding::ActionType::AcceleratePosY, sf::Vector2i(x, 3), "Move Down", context);
			addButtonLabel(Engine::KeyBinding::ActionType::Fire, sf::Vector2i(x, 4), "Fire", context);
			addButtonLabel(Engine::KeyBinding::ActionType::LaunchMissile, sf::Vector2i(x, 5), "Launch Missile", context);
		}
		// Update the labels to reflect the current key assignments.
		updateLabels();

		// Create a back button to return from the settings state.
		sf::Vector2f center = context.Window->getView().getSize() / 2.f;
		auto backButton = std::make_shared<Engine::Button>(context);
		backButton->setButtonOrigin(0, 0);
		backButton->setPosition(0, 0);
		backButton->setText(24, "Back");
		backButton->setCallback([this]
		{ requestStackPop(); });

		// Pack the back button into the GUI container.
		m_guiContainer.pack(backButton);
	}

	void SettingsState::render()
	{
		// Get the render window from the context.
		sf::RenderWindow& window = *getContext().Window;
		// Draw the background sprite and the GUI container with all buttons and labels.
		window.draw(m_backgroundSprite);
		window.draw(m_guiContainer);
	}

	bool SettingsState::update(sf::Time deltaTime)
	{
		// This state does not require continuous updates beyond event handling.
		return true;
	}

	bool SettingsState::handleEvent(const sf::Event& event)
	{
		bool isKeyBinding = false;

		// Iterate over all binding buttons to see if any is active (waiting for a key press).
		for (std::size_t i = 0; i < 2 * Engine::KeyBinding::ActionType::ActionCount; ++i)
		{
			if (m_bindingButtons[i]->isActive())
			{
				isKeyBinding = true;
				if (event.type == sf::Event::KeyReleased)
				{
					// Assign new key to Player 1 if index is in the first half.
					if (i < Engine::KeyBinding::ActionType::ActionCount)
						getContext().KeysPlayer1->assignKey(static_cast<Engine::KeyBinding::ActionType>(i), event.key.code);
						// Otherwise assign new key to Player 2.
					else
						getContext().KeysPlayer2->assignKey(static_cast<Engine::KeyBinding::ActionType>(i
							- Engine::KeyBinding::ActionType::ActionCount), event.key.code);
				}
				// Deactivate the active binding button once a key is processed.
				m_bindingButtons[i]->deactivate();
				break;
			}
		}

		// If a key binding was updated, refresh the labels; otherwise, forward the event to the GUI.
		if (isKeyBinding)
			updateLabels();
		else
			m_guiContainer.handleEvent(event);

		return false;
	}

	void SettingsState::updateLabels()
	{
		// For each action, update the labels to display the currently assigned keys.
		for (std::size_t i = 0; i < Engine::KeyBinding::ActionType::ActionCount; ++i)
		{
			auto action = static_cast<Engine::LocalPlayerAction::ActionType>(i);

			// Retrieve the assigned keys for both players.
			sf::Keyboard::Key key1 = getContext().KeysPlayer1->getAssignedKey(action);
			sf::Keyboard::Key key2 = getContext().KeysPlayer2->getAssignedKey(action);

			// Update the label for Player 1.
			m_bindingLabels[i]->setText(40, Engine::Utility::keyToString(key1));
			// Update the label for Player 2.
			m_bindingLabels[i + Engine::LocalPlayerAction::ActionType::ActionCount]->setText(40, Engine::Utility::keyToString(key2));
		}
	}

	void SettingsState::addButtonLabel(std::size_t index, sf::Vector2i offset, const std::string& text, Context context)
	{
		// Get the current screen size from the window view.
		sf::Vector2f screenSize = context.Window->getView().getSize();

		// Calculate the index offset based on which player's binding is being set.
		index += Player::ActionType::ActionCount * offset.x;

		// Create a new button for the key binding.
		m_bindingButtons[index] = std::make_shared<Engine::Button>(context);
		// Position the button based on the player's column and action index.
		m_bindingButtons[index]->setPosition(offset.x == 0 ? screenSize.x * 0.4f : screenSize.x * 0.8f,
			(index % Player::ActionType::ActionCount + 1.f) * screenSize.y * 0.14f);
		m_bindingButtons[index]->setText(18, text);
		m_bindingButtons[index]->setToggle(true);

		// Create a label to display the assigned key for the binding.
		m_bindingLabels[index] = std::make_shared<Engine::Label>("");
		// Position the label next to the corresponding button.
		m_bindingLabels[index]->setPosition(offset.x == 0 ? screenSize.x * 0.2f : screenSize.x * 0.6f,
			(index % Player::ActionType::ActionCount + 1.f) * screenSize.y * 0.14f);

		// Pack the button and label into the GUI container.
		m_guiContainer.pack(m_bindingButtons[index]);
		m_guiContainer.pack(m_bindingLabels[index]);
	}
}