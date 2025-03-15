// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef STATESTACK_H_
#define STATESTACK_H_

#include <SFML/Graphics.hpp>
#include <unordered_set>
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
	template<typename T, typename Param>
	void registerState(StateId stateId, Param arg)
	{
		m_factories[stateId] = [this, arg]()
		{
		  return State::Ptr(new T(*this, m_context, arg));
		};
	}
	void update(sf::Time deltaTime);
	void render();
	void handleEvent(const sf::Event& event);
	void pushState(StateId stateId);
	void popState();
	void clearStates();
	bool isEmpty() const;
	explicit StateStack(State::Context context);
	~StateStack() = default;
 private:
	struct PendingChange
	{
		PendingChange(StackActionType stackActionType, StateId stateId) : StackActionType(stackActionType), StateId(stateId){};
		explicit PendingChange(StackActionType stackActionType) : StackActionType(stackActionType), StateId(StateId::None){};
		StackActionType StackActionType;
		StateId StateId;
	};
	StateStack(const StateStack&);
	StateStack& operator=(const StateStack&);
	void applyPendingChanges();
	bool handleRolloverKeyEvent(const sf::Event& event);
	State::Ptr createState(StateId stateId);
	std::vector<State::Ptr> m_stack;
	std::vector<PendingChange> m_pendingList;
	State::Context m_context;
	std::map<StateId, std::function<State::Ptr()>> m_factories;
	std::unordered_set<sf::Keyboard::Key> m_rolloverPressedKeys;
	std::vector<sf::Keyboard::Key> m_allKeys;
};

#endif //STATESTACK_H_
