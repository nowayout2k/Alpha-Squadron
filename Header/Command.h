//
// Created by Johnnie Otis on 7/31/24.
//

#ifndef COMMAND_H_
#define COMMAND_H_
#include "WorldNode.h"

struct Command
{
	Command();
	std::function<void(WorldNode&, float)> action;
	unsigned int category;
};
#endif //COMMAND_H_
