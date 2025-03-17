// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef BUTTON_H_
#define BUTTON_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Component.h"
#include "Audio.h"
#include "State.h"
#include <functional>


namespace GUI
{
	class Button : public Component
	{
	 public:
		typedef std::shared_ptr<Button> Ptr;
		typedef std::function<void()> Callback;
		enum Type
		{
			Normal,
			Selected,
			Pressed,
			ButtonCount
		};
	 public:
		explicit Button(State::Context context);

		void setCallback(Callback callback);
		void setText(int size, const std::string& text);
		void setButtonOrigin(float x, float y);
		void setToggle(bool flag);

		bool isSelectable() const override;
		void select() override;
		void deselect() override;

		void activate() override;
		void deactivate() override;

		void handleEvent(const sf::Event& event) override;


	 private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void changeTexture(Type buttonType);

	 private:
		Callback m_callback;
		sf::Sprite m_sprite;
		sf::Text m_text;
		bool m_isToggle;
		Audio& m_audio;
	};
}

#endif //BUTTON_H_
