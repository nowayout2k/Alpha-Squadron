// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Component.h"
#include <functional>


namespace GUI
{
	class Button : public Component
	{
	 public:
		typedef std::shared_ptr<Button> Ptr;
		explicit Button(sf::IntRect normalTextureRect, sf::IntRect pressedTextureRect, sf::IntRect selectedTextureRect);
		bool isSelectable() const override
		{
			return true;
		}

		void handleEvent(const sf::Event& event) override
		{

		}

		void select() override;
		void deselect() override;
		void activate() override;
		void deactivate() override;
		void setCallback(std::function<void()> callback);
		void setText(unsigned int size, const std::string& text);
		void setToggle(bool flag);
	 private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		sf::Sprite m_sprite;
		sf::IntRect m_normalTextureRect;
		sf::IntRect m_selectedTextureRect;
		sf::IntRect m_pressedTextureRect;
		sf::Text m_text;
		bool m_isToggle;
		std::function<void()> m_callback;
	};
}

#endif //BUTTON_H_
