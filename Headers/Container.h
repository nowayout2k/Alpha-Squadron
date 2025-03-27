// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "Component.h"
#include "Audio.h"

#include <vector>
#include <memory>

/**
 * @file Container.h
 * @brief Declaration of the Container class.
 *
 * The Container class is a composite GUI component that manages a collection of child
 * components. It handles navigation through selectable children and forwards events to them.
 */
namespace Engine
{
	class Container : public Component
	{
	 public:
		/// Shared pointer type for Container.
		typedef std::shared_ptr<Container> Ptr;

		/**
		 * @brief Constructs an empty Container.
		 * @param audio audio reference for button clicks.
		 * Initializes the container with no selected child.
		 */
		explicit Container(Audio& audio);

		/**
		 * @brief Adds a component to the container.
		 *
		 * The component is added to the container. If no component is currently selected and
		 * the new component is selectable, it is automatically selected.
		 *
		 * @param component The component to add.
		 */
		void pack(Component::Ptr component);

		/**
		 * @brief Handles input events and forwards them to the selected child.
		 *
		 * Navigates selection based on key events (W/Up and S/Down) or forwards the event
		 * to the active child if one is selected.
		 *
		 * @param event The event to handle.
		 */
		void handleEvent(const sf::Event& event) override;

		/**
		 * @brief Checks if any child component is currently selected.
		 *
		 * @return True if a child is selected, false otherwise.
		 */
		bool hasSelection() const;

		/**
		 * @brief Determines if the container is selectable.
		 *
		 * The container itself is not selectable; its children are.
		 *
		 * @return False.
		 */
		bool isSelectable() const override;

		/**
		 * @brief Selects a child component by its index.
		 *
		 * If the child is selectable, it is selected and any previously selected child is deselected.
		 *
		 * @param index The index of the child to select.
		 */
		void select(int index);

		/**
		 * @brief Selects the next selectable child.
		 */
		void selectNext();

		/**
		 * @brief Selects the previous selectable child.
		 */
		void selectPrevious();

		/**
		 * @brief Draws the container and its children.
		 *
		 * Iterates over all child components and draws them.
		 *
		 * @param target The render target.
		 * @param states The render states.
		 */
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	 private:
		int m_selectedChild;                    ///< Index of the currently selected child.
		std::vector<Component::Ptr> m_children; ///< Collection of child components.
		Audio& m_audio;							///< audio reference for button click.
	};
}
#endif // CONTAINER_H_
