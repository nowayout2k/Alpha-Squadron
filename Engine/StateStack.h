//
// Created by Johnnie Otis on 9/2/24.
//

#ifndef STATESTACK_H_
#define STATESTACK_H_

#include <SFML/Graphics.hpp>
#include "State.h"

class StateStack
{
 public:
	enum StackActionType
	{
		Push,
		Pop,
		Clear,
	};
	template<typename T>
	void registerState(StateId stateId)
	{
		m_factories[stateId] = [this]()
		{
		  return State::Ptr(new T(*this, m_context));
		};
	}
	void update(float deltaTime);
	void render(sf::RenderStates& states);
	void handleEvent(const sf::Event& event);
	void pushState(StateId stateId);
	void popState();
	void clearStates();
	bool isEmpty() const;
	explicit StateStack(State::Context context);
	~StateStack() {}
 private:
	struct PendingChange
	{
		PendingChange(StackActionType stackActionType, StateId stateId) : stackActionType(stackActionType), stateId(stateId){};
		PendingChange(StackActionType stackActionType) : stackActionType(stackActionType), stateId(StateId::None){};
		StackActionType stackActionType;
		StateId stateId;
	};
	StateStack(const StateStack&);
	StateStack& operator=(const StateStack&);
	void applyPendingChanges();
	State::Ptr createState(StateId stateId);
	std::vector<State::Ptr> m_stack;
	std::vector<PendingChange> m_pendingList;
	State::Context m_context;
	std::map<StateId, std::function<State::Ptr()>> m_factories;
};

#endif //STATESTACK_H_
