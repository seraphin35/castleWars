//
//  Card.h
//  castlewars
//
//  Created by admin on 3/17/15.
//
//

#ifndef __castlewars__Card__
#define __castlewars__Card__

#include <iostream>
#include "Player.h"

class Player;

typedef bool (*ptrfunc)(Player *, Player *);

class Card {

private:
    int value;
    ptrfunc effect;
    //image here
public:
    Card(ptrfunc effect, int value)
    {
        this->effect = effect;
        this->value = value;
    }
    ~Card() {}
    
    const int getValue();
    const ptrfunc getEffect();
    //image getter here
};

#endif /* defined(__castlewars__File__) */
