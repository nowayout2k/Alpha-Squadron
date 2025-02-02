// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef LOADINGSTATE_H_
#define LOADINGSTATE_H_

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "ParallelTask.h"
#include "State.h"

class LoadingState : public State
{
 public:
	explicit LoadingState(StateStack& stateStack, Context& context, std::function<void()> loadingTask);
	virtual void render(sf::RenderStates& states) override;
	virtual bool update(float deltaTime) override;
	virtual bool handleEvent(const sf::Event& event) override;
 private:
	void setCompletion(float percent);
	sf::Text m_loadingText;
	sf::RectangleShape m_progressBarBackground;
	sf::RectangleShape m_progressBar;
	ParallelTask m_parallelTask;
};

#endif //LOADINGSTATE_H_
