//
// Created by Johnnie Otis on 7/31/24.
//

#ifndef COMMAND_H_
#define COMMAND_H_
#include "WorldNode.h"
#include <functional>

struct Command
{
 public:
	Command() = default;
	std::function<void(WorldNode&, float)> action;
	unsigned int nodeType = 0;
};

template <typename GameObject, typename Function>
std::function<void(WorldNode&, float)> derivedAction(Function fn)
{
	return [=] (WorldNode& node, float dt)
	{
	  fn(static_cast<GameObject&>(node), dt);
	};
}
#endif //COMMAND_H_
