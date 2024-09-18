//
// Created by Johnnie Otis on 9/2/24.
//

#ifndef STATESTACK_H_
#define STATESTACK_H_

#include <SFML/Graphics.hpp>
#include "State.h"

class StateStack : private sf::NonCopyable
{
 public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};
 public:
	explicit StateStack(State::Context context);
	template <typename T>
	void registerState(StateId stateId);
	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);
	void pushState(StateId stateId);
	void popState();
	void clearStates();
	bool isEmpty() const;
 private:
	State::Ptr createState(StateId stateId);
	void applyPendingChanges();
 private:
	struct PendingChange
	{
		Action action;
		StateId stateId;
	};
 private:
	std::vector<State::Ptr> m_stack;
	std::vector<PendingChange> m_pendingList;
	State::Context m_context;
	std::map<StateId, std::function<State::Ptr()>> m_factories;
};

#endif //STATESTACK_H_
