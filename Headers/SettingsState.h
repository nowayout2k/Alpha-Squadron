// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef SETTINGSSTATE_H_
#define SETTINGSSTATE_H_

#include "State.h"
#include "Player.h"
#include "Container.h"
#include "Button.h"
#include "Label.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <array>


class SettingsState : public State
{
 public:
	explicit SettingsState(StateStack& stack, Context context);
	virtual void render(sf::RenderStates& states) override;
	virtual bool update(float deltaTime) override;
	virtual bool handleEvent(const sf::Event& event) override;
 private:
	void updateLabels();
	void addButtonLabel(Player::ActionType action, sf::Vector2f offset, const std::string& text, Context context);
	sf::Sprite m_backgroundSprite;
	GUI::Container m_guiContainer;
	std::array<GUI::Button::Ptr, Player::ActionType::ActionCount> m_bindingButtons;
	std::array<GUI::Label::Ptr, Player::ActionType::ActionCount> m_bindingLabels;
};

#endif //SETTINGSSTATE_H_
