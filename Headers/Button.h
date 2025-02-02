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
		explicit Button();
		virtual bool isSelectable() const override
		{
			return true;
		}

		virtual void handleEvent(const sf::Event& event) override
		{

		}

		virtual void select() override;
		virtual void deselect() override;
		virtual void activate() override;
		virtual void deactivate() override;
		void setCallback(std::function<void()> callback);
		void setText(const unsigned int size, const std::string& text);
		void setToggle(bool flag);
	 private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		sf::Sprite m_sprite;
		sf::Texture m_normalTexture;
		sf::Texture m_selectedTexture;
		sf::Texture m_pressedTexture;
		sf::Text m_text;
		bool m_isToggle;
		std::function<void()> m_callback;
	};
}

#endif //BUTTON_H_
