//
// Created by Johnnie Otis on 10/12/24.
//

#ifndef PARALLELTASK_H_
#define PARALLELTASK_H_

#include <SFML/System/Mutex.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Thread.hpp>
#include <functional>

class ParallelTask
{
 public:
	ParallelTask();
	void execute(std::function<void()> task);
	bool isFinished();
	float getCompletion();
	void updateCompletion(float percentage);
 private:
	void runTask();
 private:
	std::function<void()> m_task;
	float m_completion;
	sf::Thread m_thread;
	bool m_finished;
	sf::Clock m_elapsedTime;
	sf::Mutex m_mutex;
};

#endif //PARALLELTASK_H_
