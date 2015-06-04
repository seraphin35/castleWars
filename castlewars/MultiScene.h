//
//  MultiScene.h
//  castlewars
//
//  Created by Guest User on 4/16/15.
//
//

#ifndef __castlewars__MultiScene__
#define __castlewars__MultiScene__

#include "cocos2d.h"
#include "CCDirector.h"
#include "NetworkLogic.h"

using namespace cocos2d;

class   MultiScene : public cocos2d::CCLayer
{
private:
    CCSize      screenSize;
    CCSprite    *bgMulti;
    
    CCMenuItemImage *returnBtn;
    CCMenuItemImage *playBtn;
    
    NetworkLogic    *netLog;
    bool            netRunning;
    int             joinAttempt;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    CREATE_FUNC(MultiScene);
    
    virtual bool    init();
    static CCScene  *createScene();
    
    virtual void update();
    
private:
    void        createMultiScene(CCSize);
    void        returnMenu();
    
    void    lookForGame();
    bool    isRoomAvailable();
    bool    joinRoom();
    bool    createRoom();
    void    leaveRoom();
};

#endif /* defined(__castlewars__MultiScene__) */
