// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef LOADINGSTATE_H_
#define LOADINGSTATE_H_

#include "ParallelTask.h"
#include "State.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <functional>

/**
 * @file LoadingState.h
 * @brief Declaration of the LoadingState class.
 *
 * The LoadingState class represents a state that displays a loading screen with a progress bar.
 * It executes a parallel task for loading resources and transitions to the Game state upon completion.
 */
class LoadingState : public State
{
 public:
	/**
	 * @brief Constructs a LoadingState.
	 * @param stateStack The state stack.
	 * @param context The shared state context.
	 * @param loadingTask A function to execute as a loading task.
	 */
	explicit LoadingState(StateStack& stateStack, Context& context, std::function<void()> loadingTask);

	/**
	 * @brief Renders the loading screen.
	 */
	virtual void render() override;

	/**
	 * @brief Updates the loading state.
	 * @param deltaTime The time elapsed since the last update.
	 * @return True if the state should continue, false otherwise.
	 */
	virtual bool update(sf::Time deltaTime) override;

	/**
	 * @brief Handles events while in the loading state.
	 * @param event The event to handle.
	 * @return True if the event was handled.
	 */
	virtual bool handleEvent(const sf::Event& event) override;

 private:
	/**
	 * @brief Sets the progress bar completion percentage.
	 * @param percent The completion percentage (between 0 and 1).
	 */
	void setCompletion(float percent);

	sf::Text m_loadingText;                     ///< Text displaying a loading message.
	sf::RectangleShape m_progressBarBackground; ///< Background shape for the progress bar.
	sf::RectangleShape m_progressBar;           ///< Foreground progress bar indicating completion.
	ParallelTask m_parallelTask;                ///< Task executed in parallel to load resources.
};

#endif // LOADINGSTATE_H_
