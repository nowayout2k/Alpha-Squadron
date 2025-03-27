// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef COMMAND_H_
#define COMMAND_H_

#include "WorldNode.h"

#include <functional>
#include <SFML/System/Time.hpp>

namespace Engine
{
	/**
	 * @file Command.h
	 * @brief Declaration of the Command structure and the DerivedAction helper function.
	 *
	 * The Command structure encapsulates an action to be executed on a WorldNode along with a NodeType mask.
	 * The DerivedAction template function converts a function that operates on a specific game object type
	 * into a command action that can be used in a command queue.
	 */
	struct Command
	{
		Command() = default; // Default constructor.

		std::function<void(WorldNode&, sf::Time)> Action; // Action to perform on a WorldNode.
		unsigned int NodeType = 0;                        // Node type bitmask for identifying target nodes.
	};

	/**
	 * @brief Wraps a function so that it can be used as a command action for a specific game object type.
	 *
	 * @tparam GameObject The type of WorldNode to cast to.
	 * @tparam Function The type of the function to wrap.
	 * @param fn The function to wrap.
	 * @return A function that takes a WorldNode reference and a time delta, and applies the given function
	 *         to the casted game object.
	 */
	template<typename GameObject, typename Function>
	std::function<void(WorldNode&, sf::Time)> DerivedAction(Function fn)
	{
		return [=](WorldNode& node, sf::Time dt)
		{
		  fn(static_cast<GameObject&>(node), dt);
		};
	}
}
#endif // COMMAND_H_
