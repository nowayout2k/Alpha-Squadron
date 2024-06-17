//
// Created by Johnnie Otis on 6/16/24.
//

#ifndef ICOMPONENT_H_
#define ICOMPONENT_H_

struct IComponent
{
	virtual void update(float deltaTime) = 0;
};

#endif //ICOMPONENT_H_
