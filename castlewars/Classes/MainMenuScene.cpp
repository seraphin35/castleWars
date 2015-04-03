#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

CCScene* MainMenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainMenu *layer = MainMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // get screen size
	CCSize  screenSize = CCDirector::sharedDirector()->getWinSize();

    // add background to Main menu
    CCSprite* bgMenu = CCSprite::create("BackgroundMenu.png");
    bgMenu->setScaleX(screenSize.width / bgMenu->getContentSize().width);
    bgMenu->setScaleY(screenSize.height / bgMenu->getContentSize().height);
    bgMenu->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(bgMenu, 0);

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(MainMenu::menuCloseCallback)
                                                          );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 30, 50) );
    
    // create and initialize buttons
    this->onePlayerButton = CCMenuItemImage::create("ButtonOnePlayer.png",
                                                    "ButtonOnePlayer.png",
                                                    this,
                                                    menu_selector(MainMenu::menuCloseCallback)
                                                    );
    this->multiPlayerButton = CCMenuItemImage::create("ButtonMultiplayer.png",
                                                      "ButtonMultiplayer.png",
                                                      this,
                                                      menu_selector(MainMenu::menuCloseCallback)
                                                      );
    
    // create and initialize titles for buttons
    this->onePlayerTitle = CCLabelTTF::create("One Player", "MagicFont", 30,
                                              CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->multiPlayerTitle = CCLabelTTF::create("Multiplayer", "MagicFont", 30,
                                                CCSizeMake(245, 32), kCCTextAlignmentCenter);
    
    // set titles color
    this->onePlayerTitle->setColor(ccc3(50, 50, 250));
    this->multiPlayerTitle->setColor(ccc3(50, 50, 250));
    
    // set buttons position
    this->onePlayerButton->setPosition(screenSize.width / 4,
                                       screenSize.height / 2);
    this->multiPlayerButton->setPosition(screenSize.width / 4 * 3,
                                         screenSize.height / 2);
    
    // set buttons titles positions
    this->onePlayerTitle->setPosition( ccp(screenSize.width / 4 - 50,
                                          screenSize.height / 2 + 150) );
    this->multiPlayerTitle->setPosition( ccp(screenSize.width / 4 * 3 - 50,
                                            screenSize.height / 2 + 150) );
    
    // add all elements as a child to this layer
    this->addChild(onePlayerButton, 1);
    this->addChild(multiPlayerButton, 1);

    this->addChild(onePlayerTitle, 2);
    this->addChild(multiPlayerTitle, 2);
    
    this->schedule(schedule_selector(MainMenu::update));
    
    return true;
}

void MainMenu::update(float dt)
{
    
}

void MainMenu::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
