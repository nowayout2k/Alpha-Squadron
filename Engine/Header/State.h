//
// Created by Johnnie Otis on 9/2/24.
//

#ifndef STATE_H_
#define STATE_H_

#include "../Header/StateStack.h"
#include "../Header/StateIdentifiers.h"
#include "../Header/Input.h"

class State
{
 public:
	typedef std::unique_ptr<State> Ptr;
	struct Context
	{
	};
 public:
	State(StateStack& stack, Context context);
	virtual ~State();
	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;
 protected:
	void requestStackPush(StateId stateId);
	void requestStackPop();
	void requestStateClear();
	Context getContext() const;
 private:
	StateStack* m_stack;
	Context m_context;
};

#endif //STATE_H_
