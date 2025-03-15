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
		Button(State::Context context);

		void setCallback(Callback callback);
		void setText(const int size, const std::string& text);
		void setToggle(bool flag);

		virtual bool isSelectable() const;
		virtual void select();
		virtual void deselect();

		virtual void activate();
		virtual void deactivate();

		virtual void handleEvent(const sf::Event& event);


	 private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
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
