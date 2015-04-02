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
#include "cocos2d.h"

class Player;

typedef bool (*ptrfunc)(Player *, Player *);

class Card {

private:
    int value;
    ptrfunc effect;
    cocos2d::CCSprite* image;
public:
    Card(ptrfunc effect, int value, cocos2d::CCSprite* image);
    ~Card() {}
    
    const int getValue();
    const ptrfunc getEffect();
    const cocos2d::CCSprite* getImage();
    //image getter here
};

#endif /* defined(__castlewars__File__) */
