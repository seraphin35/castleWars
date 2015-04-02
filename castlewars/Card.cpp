//
//  File.cpp
//  castlewars
//
//  Created by admin on 3/17/15.
//
//

#include "Card.h"

Card::Card(ptrfunc effect, int value, cocos2d::CCSprite* image)
{
    this->effect = effect;
    this->value = value;
}

const int Card::getValue()
{
    return this->value;
}

const ptrfunc Card::getEffect()
{
    return this->effect;
}

const cocos2d::CCSprite* Card::getImage()
{
    return this->image;
}