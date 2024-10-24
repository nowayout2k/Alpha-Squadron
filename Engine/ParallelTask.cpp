//
// Created by Johnnie Otis on 10/12/24.
//

#include <SFML/System/Lock.hpp>
#include "ParallelTask.h"

ParallelTask::ParallelTask() : m_thread(&ParallelTask::runTask, this), m_finished(false) {}

bool ParallelTask::isFinished()
{
	sf::Lock lock(m_mutex);
	return m_finished;
}

void ParallelTask::runTask()
{
	if (m_task)
	{
		{
			sf::Lock lock(m_mutex);
			m_completion = 0.f;
		}

		m_task();

		{
			sf::Lock lock(m_mutex);
			m_finished = true;
			m_completion = 1.f;
		}
	}
}
void ParallelTask::execute(std::function<void()> task)
{
	{
		sf::Lock lock(m_mutex);
		m_finished = false;
		m_completion = 0.f;
	}
	m_task = task;
	m_thread.launch();
}

float ParallelTask::getCompletion()
{
	sf::Lock lock(m_mutex);
	return m_completion;
}
void ParallelTask::updateCompletion(float percentage)
{
	sf::Lock lock(m_mutex);
	m_completion += percentage;
}
