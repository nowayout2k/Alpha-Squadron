// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef LABEL_H_
#define LABEL_H_

#include "Component.h"

#include <SFML/Graphics/Text.hpp>

namespace Engine
{
	/**
	 * @file Label.h
	 * @brief Declaration of the Label class.
	 *
	 * The Label class is a GUI component used for displaying non-interactive text.
	 * It does not support selection or activation.
	 */
	class Label : public Component
	{
	 public:
		/// Shared pointer type for Label.
		typedef std::shared_ptr<Label> Ptr;

		/**
		 * @brief Constructs a Label with the given text.
		 * @param text The text to display.
		 */
		explicit Label(const std::string& text);

		/**
		 * @brief Indicates whether the label is selectable.
		 * @return Always false since labels are non-interactive.
		 */
		virtual bool isSelectable() const;

		/**
		 * @brief Sets the text and character size for the label.
		 * @param size The character size.
		 * @param text The string to display.
		 */
		void setText(const unsigned int size, const std::string& text);

		/**
		 * @brief Handles input events.
		 * @param event The event to process.
		 */
		virtual void handleEvent(const sf::Event& event);

	 private:
		/**
		 * @brief Draws the label.
		 * @param target The render target.
		 * @param states The render states.
		 */
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Text m_text; ///< The SFML text object used to display the label.
	};
}
#endif // LABEL_H_
