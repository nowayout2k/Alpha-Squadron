//
// Created by Johnnie Otis on 8/12/24.
//

#ifndef COMMANDQUEUE_H_
#define COMMANDQUEUE_H_

#include <queue>
#include "Command.h"

class CommandQueue
{
 public:
	void push(const Command& command) { m_queue.push(command); }
	Command pop()
	{
		if (m_queue.empty())
			throw std::runtime_error("Queue is empty");

		Command c = m_queue.front();
		m_queue.pop();
		return c;
	}
	bool isEmpty() const { return m_queue.empty(); }
	std::queue<Command>::size_type size() const { return m_queue.size(); }
 private:
	std::queue<Command> m_queue;
};
#endif //COMMANDQUEUE_H_
