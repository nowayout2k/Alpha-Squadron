//
// Created by Johnnie Otis on 9/2/24.
//

#ifndef STATE_H_
#define STATE_H_

#include "StateIdentifiers.h"
#include "GameplayInput.h"

class StateStack;

class State
{
 public:
	typedef std::unique_ptr<State> Ptr;
	struct Context
	{
		Context(sf::RenderWindow& window, GameplayInput& input) : window(&window), input(&input){};
		sf::RenderWindow* window;
		GameplayInput* input;
	};
 public:
	State(StateStack& stack, Context context) : m_stack(&stack), m_context(context) {}
	virtual ~State() {};
	virtual void render(sf::RenderStates& states) = 0;
	virtual bool update(float deltaTime) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;
 protected:
	void requestStackPush(StateId stateId);
	void requestStackPop();
	void requestStateClear();
	Context getContext() const { return m_context; }
 private:
	StateStack* m_stack;
	Context m_context;
};

#endif //STATE_H_
