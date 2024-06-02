//
// Created by Johnnie Otis on 6/2/24.
//

#ifndef ALPHA_SQUADRON_SCROLLINGBACKGROUND_H
#define ALPHA_SQUADRON_SCROLLINGBACKGROUND_H


#include "SpriteEntity.h"

class ScrollingBackground : public SpriteEntity
{
public:
    ScrollingBackground(const std::string &pathToTexture);
    void Update(float deltaTime) override;
};


#endif //ALPHA_SQUADRON_SCROLLINGBACKGROUND_H
