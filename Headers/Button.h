// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Audio.h"
#include "Component.h"
#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <functional>

/**
 * @file Button.h
 * @brief Declares the Button class for GUI components.
 *
 * The Button class is a GUI component that responds to user input.
 * It displays a sprite and text, manages selection state, and triggers a callback when activated.
 */
namespace GUI
{
	class Button : public Component
	{
	 public:
		/// Shared pointer type for Button.
		typedef std::shared_ptr<Button> Ptr;
		/// Function type for button callbacks.
		typedef std::function<void()> Callback;

		/**
		 * @brief Enumeration of button visual states.
		 */
		enum Type
		{
			Normal,    ///< Default button appearance.
			Selected,  ///< Appearance when the button is selected.
			Pressed,   ///< Appearance when the button is pressed.
			ButtonCount
		};

		/**
		 * @brief Constructs a Button.
		 * @param context Provides access to shared resources such as Audio.
		 */
		explicit Button(State::Context context);

		/**
		 * @brief Sets the callback function to be executed when the button is activated.
		 * @param callback The callback function.
		 */
		void setCallback(Callback callback);

		/**
		 * @brief Sets the text displayed on the button.
		 * @param size The character size.
		 * @param text The string to display.
		 */
		void setText(int size, const std::string& text);

		/**
		 * @brief Sets the origin of the button sprite and repositions the text.
		 * @param x The x-coordinate of the origin.
		 * @param y The y-coordinate of the origin.
		 */
		void setButtonOrigin(float x, float y);

		/**
		 * @brief Sets whether the button toggles its state when activated.
		 * @param flag True if the button should toggle, false otherwise.
		 */
		void setToggle(bool flag);

		/**
		 * @brief Checks if the button is selectable.
		 * @return True if selectable.
		 */
		bool isSelectable() const override;

		/**
		 * @brief Selects the button and updates its texture.
		 */
		void select() override;

		/**
		 * @brief Deselects the button and resets its texture.
		 */
		void deselect() override;

		/**
		 * @brief Activates the button, triggering its callback and playing a sound.
		 */
		void activate() override;

		/**
		 * @brief Deactivates the button and resets its texture if it is a toggle button.
		 */
		void deactivate() override;

		/**
		 * @brief Handles incoming events.
		 * @param event The event to handle.
		 */
		void handleEvent(const sf::Event& event) override;

	 private:
		/**
		 * @brief Draws the button.
		 * @param target The render target.
		 * @param states The render states.
		 */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		/**
		 * @brief Changes the button's texture based on its state.
		 * @param buttonType The new visual state.
		 */
		void changeTexture(Type buttonType);

		Callback m_callback;  ///< Callback function to execute on activation.
		sf::Sprite m_sprite;  ///< Sprite representing the button.
		sf::Text m_text;      ///< Text displayed on the button.
		bool m_isToggle;      ///< Flag indicating whether the button is toggleable.
		Audio& m_audio;       ///< Reference to the audio system.
	};
}

#endif // BUTTON_H_
