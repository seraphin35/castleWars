#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class Game : public cocos2d::CCLayer
{
private:
    int turn;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    virtual void update(float);
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void nextTurn(CCObject *pSend);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(Game);
};

#endif // __HELLOWORLD_SCENE_H__
