//
//  GameOverScene.h
//  castlewars
//
//  Created by Guest User on 4/16/15.
//
//

#ifndef __castlewars__GameOverScene__
#define __castlewars__GameOverScene__

#include <iostream>
#include "MainMenuScene.h"
#include "Player.h"
#include "CCDirector.h"
#include "cocos2d.h"

using namespace cocos2d;

class   GameOver : public cocos2d::CCLayer
{
private:
    CCSize  screenSize;

    CCSprite    *bgGameOver;
    std::vector<CCLabelTTF *>   endValues;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    CREATE_FUNC(GameOver);
    
    virtual bool    init();
    
    static CCScene  *createScene();
    
private:
    void    createStatScene(CCSize);

    CCMenuItemImage *createButton(const char *plain, const char *focus, int tag,
                                  int posX, int posY, float scale,
                                  SEL_MenuHandler callBack);
    void    mainMenu();
    void    endButton(CCObject *);
};

#endif /* defined(__castlewars__GameOverScene__) */