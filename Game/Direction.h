//
// Created by Johnnie Otis on 11/30/24.
//

#ifndef DIRECTION_H_
#define DIRECTION_H_

struct Direction
{
	Direction(float angle, float distance) : angle(angle), distance(distance){}
	float angle;
	float distance;
};

#endif //DIRECTION_H_
