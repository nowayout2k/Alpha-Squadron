// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef NODETYPE_H_
#define NODETYPE_H_

#include <string>

enum class NodeType
{
	None = 0,
	WorldNode = 1 << 0,
	GameSprite = 1 << 1,
	Text = 1 << 2,
	Aircraft = 1 << 3,
	Player = 1 << 4,
	ParticleSystem = 1 << 5,
	Enemy = 1 << 6,
	EnemyProjectile = 1 << 7,
	AlliedProjectile = 1 << 8,
	SpriteFrontLayer = 1 << 9,
	Pickup = 1 << 10,
	UiCanvas = 1 << 11
};



#endif //NODETYPE_H_
