#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "CCDirector.h"
#include "GameScene.h"
#include "SRes.h"

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
    SRes::getInstance().initRessources();
    
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // get screen size
	CCSize  screenSize = CCDirector::sharedDirector()->getWinSize();

    std::srand(arc4random());
    
    // add background to Main menu
    CCSprite* bgMenu = CCSprite::create("menuBG.png");
    bgMenu->setScaleX(screenSize.width / bgMenu->getContentSize().width);
    bgMenu->setScaleY(screenSize.height / bgMenu->getContentSize().height);
    bgMenu->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(bgMenu, 0);
    
    // create and initialize buttons
    this->onePlayerButton = CCMenuItemImage::create("soloBtn.png",
                                                    "soloBtn.png",
                                                    this,
                                                    menu_selector(MainMenu::onePlayerMode)
                                                    );
    this->multiPlayerButton = CCMenuItemImage::create("multiBtn.png",
                                                      "multiBtn.png",
                                                      this,
                                                      menu_selector(MainMenu::multiplayerMode)
                                                      );
    this->statButton = CCMenuItemImage::create("statsBtn.png",
                                               "statsBtn.png",
                                               this,
                                               menu_selector(MainMenu::statMode)
                                               );
    
    this->quitButton = CCMenuItemImage::create("CloseNormal.png",
                                               "CloseSelected.png",
                                               this,
                                               menu_selector(MainMenu::menuCloseCallback)
                                               );
    
    quitButton->setPosition( ccp(screenSize.width - 30, 50) );
    
    // create and initialize titles for buttons
    this->onePlayerTitle = CCLabelTTF::create("One Player", "MagicFont", 30,
                                              CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->multiPlayerTitle = CCLabelTTF::create("Multiplayer", "MagicFont", 30,
                                                CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->statTitle = CCLabelTTF::create("Statistiques", "MagicFont", 30,
                                          CCSizeMake(245, 32), kCCTextAlignmentCenter);
    
    // set titles color
    this->onePlayerTitle->setColor(ccc3(50, 50, 250));
    this->multiPlayerTitle->setColor(ccc3(50, 50, 250));
    this->statTitle->setColor(ccc3(50, 50, 250));
    
    // set buttons scale
    this->onePlayerButton->setScale(0.9);
    this->multiPlayerButton->setScale(0.9);
    this->statButton->setScale(0.9);
    
    // set buttons position
    this->onePlayerButton->setPosition(screenSize.width / 4 - 20,
                                       screenSize.height / 2);
    this->multiPlayerButton->setPosition(screenSize.width / 4 * 2,
                                         screenSize.height / 2);
    this->statButton->setPosition(screenSize.width / 4 * 3,
                                         screenSize.height / 2);
    
    // set buttons titles positions
    this->onePlayerTitle->setPosition( ccp(screenSize.width / 4 - 40,
                                           screenSize.height / 2 + 135) );
    this->multiPlayerTitle->setPosition( ccp(screenSize.width / 4 * 2 - 40,
                                             screenSize.height / 2 + 135) );
    this->statTitle->setPosition( ccp(screenSize.width / 4 * 3 - 40,
                                             screenSize.height / 2 + 135) );
    
    // create menu, it's an autorelease object
    this->menu = CCMenu::create(this->onePlayerButton, this->multiPlayerButton, this->statButton,
                                this->quitButton, NULL);
    menu->setPosition( CCPointZero );
    this->addChild(menu, 1);
    
    // add titles elements as a child to this layer
    this->addChild(onePlayerTitle, 2);
    this->addChild(multiPlayerTitle, 2);
    this->addChild(statTitle, 2);
    
    this->schedule(schedule_selector(MainMenu::update));
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mainMenu.mp3", true);
    
    return true;
}

void MainMenu::update(float dt)
{
    
}

void MainMenu::onePlayerMode(CCObject* pSender)
{
    printf("Game launched");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCScene *gameScene = Game::createScene();
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.8, gameScene));
}

void MainMenu::multiplayerMode(CCObject* pSender)
{
    
}

void MainMenu::statMode(CCObject* pSender)
{
    
}

void MainMenu::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
