// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef COMMANDQUEUE_H_
#define COMMANDQUEUE_H_

#include <queue>
#include "Command.h"

namespace Engine
{
	/**
	 * @file CommandQueue.h
	 * @brief Declaration of the CommandQueue class.
	 *
	 * The CommandQueue class provides a simple interface for managing a queue of Command objects.
	 * It allows pushing commands into the queue and retrieving them for processing.
	 */
	class CommandQueue
	{
	 public:
		/**
		 * @brief Pushes a command onto the queue.
		 * @param command The command to be added.
		 */
		void push(const Command& command)
		{
			m_queue.push(command);
		}

		/**
		 * @brief Pops the front command from the queue.
		 *
		 * If the queue is empty, a runtime error is thrown.
		 * @return The command that was at the front of the queue.
		 * @throws std::runtime_error if the queue is empty.
		 */
		Command pop()
		{
			if (m_queue.empty())
				throw std::runtime_error("Queue is empty");

			Command c = m_queue.front();
			m_queue.pop();
			return c;
		}

		/**
		 * @brief Checks whether the queue is empty.
		 * @return True if the queue is empty; false otherwise.
		 */
		bool isEmpty() const
		{
			return m_queue.empty();
		}

		/**
		 * @brief Returns the number of commands in the queue.
		 * @return The size of the command queue.
		 */
		std::queue<Command>::size_type size() const
		{
			return m_queue.size();
		}

	 private:
		std::queue<Command> m_queue; ///< Underlying container for commands.
	};
}
#endif // COMMANDQUEUE_H_
