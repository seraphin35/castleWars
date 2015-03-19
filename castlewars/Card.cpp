//
//  File.cpp
//  castlewars
//
//  Created by admin on 3/17/15.
//
//

#include "Card.h"

const int Card::getValue()
{
    return this->value;
}

const ptrfunc Card::getEffect()
{
    return this->effect;
}