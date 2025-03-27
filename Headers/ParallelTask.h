// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file ParallelTask.h
 * @brief Declares the ParallelTask class for executing tasks in parallel.
 *
 * This header provides an interface for executing a function in a separate thread.
 * It enables asynchronous task execution, progress tracking, and thread-safe status checks.
 */

#ifndef PARALLELTASK_H_
#define PARALLELTASK_H_

#include <SFML/System/Mutex.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Thread.hpp>
#include <functional>

/**
 * @class ParallelTask
 * @brief Executes a given task in a separate thread.
 *
 * The ParallelTask class allows asynchronous execution of a function using SFML's threading utilities.
 * It tracks the task's progress and provides methods to check if the task is finished.
 */
class ParallelTask
{
 public:
	/**
	 * @brief Constructs a ParallelTask object.
	 *
	 * Initializes internal thread, mutex, clock, and the finished flag.
	 */
	ParallelTask();

	/**
	 * @brief Executes the provided task asynchronously.
	 * @param task A function object representing the task to execute.
	 */
	void execute(std::function<void()> task);

	/**
	 * @brief Checks if the task has completed execution.
	 * @return True if the task is finished, false otherwise.
	 */
	bool isFinished();

	/**
	 * @brief Gets the current completion percentage of the task.
	 * @return A float value between 0.0 (not started) and 1.0 (complete).
	 */
	float getCompletion();

	/**
	 * @brief Updates the internal completion percentage.
	 * @param percentage The incremental percentage to add to the current completion.
	 */
	void updateCompletion(float percentage);

 private:
	/**
	 * @brief Runs the assigned task and updates the completion status.
	 *
	 * This method is executed in a separate thread. It resets the completion,
	 * calls the task function, and marks the task as finished upon completion.
	 */
	void runTask();

 private:
	std::function<void()> m_task; 	///< The function representing the task to execute.
	float m_completion;///< The current completion percentage of the task (0.0 to 1.0).
	sf::Thread m_thread;///< SFML thread used to run the task concurrently.
	bool m_finished;///< Flag indicating whether the task has finished execution.
	sf::Clock m_elapsedTime;///< Clock to measure elapsed time since the task started.
	sf::Mutex m_mutex;///< Mutex to protect shared data during multithreaded execution.
};

#endif //PARALLELTASK_H_
