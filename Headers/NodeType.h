// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef NODETYPE_H_
#define NODETYPE_H_

#include <string>

enum class NodeType
{
	None = 0,
	WorldNode = 1 << 0,
	Entity = 1 << 1,
	Sprite = 1 << 2,
	Text = 1 << 3,
	Aircraft = 1 << 4,
	Player = 1 << 5,
	Ally = 1 << 6,
	Enemy = 1 << 7,
	EnemyProjectile = 1 << 8,
	AlliedProjectile = 1 << 9,
	CollisionLayer = 1 << 10,
	Pickup = 1 << 11,
};



#endif //NODETYPE_H_
