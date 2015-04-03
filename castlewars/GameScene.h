//
//  GameScene.h
//  castlewars
//
//  Created by Guest User on 4/3/15.
//
//

#ifndef __castlewars__GameScene__
#define __castlewars__GameScene__

#include "cocos2d.h"
#include "Player.h"

using namespace cocos2d;

class   Game : cocos2d::CCLayer
{
private:
    int             turn;
    bool            currentPlayerTurn;
    
private:
    Player*     p1;
    Player*     p2;
    
    CCString    pMagicStr;
    CCString    pGemsStr;

    CCLabelTTF* p1Magic;
    CCLabelTTF* p1Gems;
    CCLabelTTF* p1Name;
    
    CCString    comMagicStr;
    CCString    comGemsStr;

    CCLabelTTF* p2Magic;
    CCLabelTTF* p2Gems;
    CCLabelTTF* p2Name;

public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    virtual void update(float);

public:
    void nextTurn(CCObject *pSend);
    void startNewTurn(Player *p);
    void switchTurn(bool extra);
    
};

#endif /* defined(__castlewars__GameScene__) */
