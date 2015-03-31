#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <string>

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* Game::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Game *layer = Game::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(Game::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
    CCMenuItemImage *turnButton = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(Game::nextTurn));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, turnButton, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    CCString turnStr = *CCString::createWithFormat("%d", this->turn);
    CCLabelTTF* pLabel = CCLabelTTF::create(turnStr.getCString(), "Thonburi", 42);
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    // add "Game" splash screen"
    CCSprite* pSprite = CCSprite::create("BackgroundMenu.png");
    
    // position the sprite on the center of the screen
    turnButton->setPosition(ccp(size.width / 2, size.height / 2));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    this->schedule(schedule_selector(Game::update));
    
    return true;
}

void Game::update(float dt)
{
    
}

void Game::nextTurn(CCObject *pSend)
{
    this->turn += 1;
    printf("%d", this->turn);
}

void Game::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
