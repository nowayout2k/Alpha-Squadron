// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

/**
 * @file Component.h
 * @brief Declaration of the Component class for GUI elements.
 *
 * The Component class provides a base interface for GUI components.
 * It inherits from sf::Drawable and sf::Transformable, and is non-copyable.
 */
namespace GUI
{
	class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	 public:
		/// Shared pointer type for Component.
		typedef std::shared_ptr<Component> Ptr;

		/**
		 * @brief Constructs a Component.
		 */
		Component();

		/**
		 * @brief Virtual destructor.
		 */
		virtual ~Component() override;

		/**
		 * @brief Checks if the component is selected.
		 * @return True if selected.
		 */
		bool isSelected() const;

		/**
		 * @brief Selects the component.
		 */
		virtual void select();

		/**
		 * @brief Deselects the component.
		 */
		virtual void deselect();

		/**
		 * @brief Checks if the component is active.
		 * @return True if active.
		 */
		virtual bool isActive() const;

		/**
		 * @brief Activates the component.
		 */
		virtual void activate();

		/**
		 * @brief Deactivates the component.
		 */
		virtual void deactivate();

		/**
		 * @brief Checks if the component is selectable.
		 * @return True if selectable.
		 */
		virtual bool isSelectable() const = 0;

		/**
		 * @brief Handles an incoming event.
		 * @param event The event to handle.
		 */
		virtual void handleEvent(const sf::Event& event) = 0;

		/**
		 * @brief Draws the component.
		 * @param target The render target.
		 * @param states The current render states.
		 */
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

	 private:
		bool m_isSelected; ///< Indicates whether the component is selected.
		bool m_isActive;   ///< Indicates whether the component is active.
	};
}

#endif // COMPONENT_H_
