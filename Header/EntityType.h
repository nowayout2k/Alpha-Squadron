//
// Created by Johnnie Otis on 6/29/24.
//

#ifndef ENTITYTYPE_H_
#define ENTITYTYPE_H_

enum class EntityType
{
	None = 0x0,
	Player = 0x1,
	Enemy = 0x2,
	Projectile = 0x4,
	Background = 0x8,
	UI = 0xA
};

#endif //ENTITYTYPE_H_
