//
// Created by Johnnie Otis on 6/2/24.
//

#ifndef ALPHA_SQUADRON_HEADER_SCROLLINGBACKGROUND_H_
#define ALPHA_SQUADRON_HEADER_SCROLLINGBACKGROUND_H_


#include "SpriteEntity.h"

class ScrollingBackground : public SpriteEntity
{
public:
    ScrollingBackground();
    void update(float deltaTime) override;
};


#endif //ALPHA_SQUADRON_HEADER_SCROLLINGBACKGROUND_H_
