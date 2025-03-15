// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef STATE_H_
#define STATE_H_

#include "StateIdentifiers.h"
#include "Player.h"

class StateStack;

class State
{
 public:
	typedef std::unique_ptr<State> Ptr;
	struct Context
	{
		Context(sf::RenderWindow& window, Audio& audio, KeyBinding& keys1, KeyBinding& keys2) : Window(&window), Audio(&audio), KeysPlayer1(&keys1), KeysPlayer2(&keys2) {};
		sf::RenderWindow* Window;
		Audio* Audio;
		KeyBinding* KeysPlayer1;
		KeyBinding* KeysPlayer2;
	};
 public:
	State(StateStack& stack, Context context) : m_stack(&stack), m_context(context) {}
	virtual ~State() = default;
	virtual void render() = 0;
	virtual bool update(sf::Time deltaTime) = 0;
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
