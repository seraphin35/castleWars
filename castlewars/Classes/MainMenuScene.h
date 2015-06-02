#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include <string>

#include "cocos2d.h"
#include "Player.h"

using namespace cocos2d;

class MainMenu : public cocos2d::CCLayer
{
private:
    CCMenu*             menu;
    
    CCMenuItemImage*    onePlayerButton;
    CCMenuItemImage*    multiPlayerButton;
    CCMenuItemImage*    statButton;
    CCMenuItemImage*    quitButton;
    
    CCLabelTTF*         onePlayerTitle;
    CCLabelTTF*         multiPlayerTitle;
    CCLabelTTF*         statTitle;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    void    preloadAudio();
    
    virtual void update(float);
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void onePlayerMode(CCObject* pSender);
    void multiplayerMode(CCObject* pSender);
    void statMode(CCObject* pSender);
    void menuCloseCallback(CCObject* pSender);

    void startOnlineGame();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__
