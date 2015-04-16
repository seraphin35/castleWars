//
//  StatScene.h
//  castlewars
//
//  Created by Guest User on 4/16/15.
//
//

#ifndef __castlewars__StatScene__
#define __castlewars__StatScene__

#include "cocos2d.h"
#include "CCDirector.h"

using namespace cocos2d;

class   Stat : public cocos2d::CCLayer
{
private:
    CCSize      screenSize;
    CCSprite    *bgStat;
    
    CCMenuItemImage *returnBtn;

public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    CREATE_FUNC(Stat);
    
    virtual bool    init();
    static CCScene  *createScene();

private:
    void        createStatScene(CCSize);
    void        returnMenu();
};

#endif /* defined(__castlewars__StatScene__) */
