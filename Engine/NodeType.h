//
// Created by Johnnie Otis on 6/29/24.
//

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
	Projectile = 1 << 8,
	CollisionLayer = 1 << 9,
};

inline std::string NodeTypeToString(NodeType type)
{
	switch(type)
	{
	case NodeType::None:
		return "None";
	case NodeType::WorldNode:
		return "WorldNode";
	case NodeType::Entity:
		return "Entity";
	case NodeType::Sprite:
		return "Sprite";
	case NodeType::Text:
		return "Text";
	case NodeType::Aircraft:
		return "Aircraft";
	case NodeType::Player:
		return "Player";
	case NodeType::Ally:
		return "Ally";
	case NodeType::Enemy:
		return "Enemy";
	case NodeType::Projectile:
		return "Projectile";
	default:
		return "None";
	}
}

#endif //NODETYPE_H_
