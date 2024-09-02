//
// Created by Johnnie Otis on 9/2/24.
//

#ifndef STATESTACK_H_
#define STATESTACK_H_

#include <SFML/Graphics.hpp>

class StateStack : private sf::NonCopyable
{
 /*public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};
 public:
	explicit StateStack(State::Context context);
	template <typename T>
	void registerState(States::ID stateID);
	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);
	void pushState(States::ID stateID);
	void popState();
	void clearStates();
	bool isEmpty() const;
 private:
	State::Ptr createState(States::ID stateID);
	void applyPendingChanges();
 private:
	struct PendingChange
	{
		...
		Action action;
		States::ID stateID;
	};
 private:
	std::vector<State::Ptr> mStack;
	std::vector<PendingChange> mPendingList;
	State::Context mContext;
	std::map<States::ID,
	std::function<State::Ptr()>> mFactories;*/
};

#endif //STATESTACK_H_
