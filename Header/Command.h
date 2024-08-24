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
#endif //COMMAND_H_
