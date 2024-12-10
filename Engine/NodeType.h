//
// Created by Johnnie Otis on 6/29/24.
//

#ifndef NODETYPE_H_
#define NODETYPE_H_

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
	Projectile = 1 << 8,

};

#endif //NODETYPE_H_
