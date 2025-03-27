// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file ParallelTask.cpp
 * @brief Implements the ParallelTask class methods.
 *
 * This source file provides the implementation for executing tasks in a separate thread,
 * checking for task completion, and updating task progress in a thread-safe manner.
 */

#include <SFML/System/Lock.hpp>
#include "../Headers/ParallelTask.h"

ParallelTask::ParallelTask()
	: m_thread(&ParallelTask::runTask, this), m_finished(false)
{
	// Constructor initializes the thread with the runTask member function.
}

bool ParallelTask::isFinished()
{
	// Lock the mutex to safely read the finished flag.
	sf::Lock lock(m_mutex);
	return m_finished;
}

void ParallelTask::runTask()
{
	// Check if a valid task has been assigned.
	if (m_task)
	{
		{
			// Lock the mutex to safely reset the completion percentage.
			sf::Lock lock(m_mutex);
			m_completion = 0.f;
		}

		// Execute the task.
		m_task();

		{
			// Lock the mutex to safely update the finished flag and set completion to 1.
			sf::Lock lock(m_mutex);
			m_finished = true;
			m_completion = 1.f;
		}
	}
}

void ParallelTask::execute(std::function<void()> task)
{
	{
		// Lock the mutex to reset the finished flag and completion percentage.
		sf::Lock lock(m_mutex);
		m_finished = false;
		m_completion = 0.f;
	}
	// Assign the task and launch the thread to execute it.
	m_task = task;
	m_thread.launch();
}

float ParallelTask::getCompletion()
{
	// Lock the mutex to safely return the current completion value.
	sf::Lock lock(m_mutex);
	return m_completion;
}

void ParallelTask::updateCompletion(float percentage)
{
	// Lock the mutex to safely update the completion percentage.
	sf::Lock lock(m_mutex);
	m_completion += percentage;
}
