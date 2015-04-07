//
//  GameScene.cpp
//  castlewars
//
//  Created by Guest User on 4/3/15.
//
//

#include "GameScene.h"
#include "cocos2d.h"

CCScene* Game::createScene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    CCLayer *layer = Game::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool    Game::init()
{
    // get screen size
	CCSize  screenSize = CCDirector::sharedDirector()->getWinSize();
    
    // create and add game background
    CCSprite* bgGame = CCSprite::create("BackgroundGame.png");
    bgGame->setScaleX(screenSize.width / bgGame->getContentSize().width);
    bgGame->setScaleY(screenSize.height / bgGame->getContentSize().height);
    bgGame->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    
    this->p1 = new Player();
    this->p2 = new Player();
    
    // Create magic and gems numbers as string
    CCString pMagicStr =   *CCString::createWithFormat("%d", this->p1->getMagic());
    this->p1Magic   =   CCLabelTTF::create(pMagicStr.getCString(), "Thonburi", 30,
                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    
    CCString pGemsStr  =   *CCString::createWithFormat("%d", this->p1->getCrystals());
    this->p1Gems    =   CCLabelTTF::create(pGemsStr.getCString(), "Thonburi", 25,
                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    
    CCString comMagicStr   =   *CCString::createWithFormat("%d", this->p2->getMagic());
    this->p2Magic       =   CCLabelTTF::create(comMagicStr.getCString(), "Thonburi", 30,
                                               CCSizeMake(245, 32), kCCTextAlignmentCenter);

    CCString comGemsStr    =   *CCString::createWithFormat("%d", this->p2->getCrystals());
    this->p2Gems        =  CCLabelTTF::create(comGemsStr.getCString(), "Thonburi", 25,
                                              CCSizeMake(245, 32), kCCTextAlignmentCenter);
    
    CCString p1CastleStr    =   *CCString::createWithFormat("%d", this->p1->getCastle());
    CCString p1WallStr  =   *CCString::createWithFormat("%d", this->p1->getWall());
    CCString p2CastleStr    =   *CCString::createWithFormat("%d", this->p2->getCastle());
    CCString p2WallStr  =   *CCString::createWithFormat("%d", this->p2->getWall());
    
    this->p1Castle = CCLabelTTF::create(p1CastleStr.getCString(), "Thonburi", 30,
                                      CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p1Wall = CCLabelTTF::create(p1WallStr.getCString(), "Thonburi", 30,
                                      CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p2Castle = CCLabelTTF::create(p2CastleStr.getCString(), "Thonburi", 30,
                                        CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p2Wall = CCLabelTTF::create(p2WallStr.getCString(), "Thonburi", 30,
                                      CCSizeMake(245, 32), kCCTextAlignmentCenter);
    
    // create names
    this->p1Name    = CCLabelTTF::create("Player 1", "Helvetica", 30,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p2Name    = CCLabelTTF::create("Computer", "Helvetica", 30,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);

    // set all positions
    bgGame->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    
    p1Magic->setPosition(ccp(90, screenSize.height - 30));
    p1Gems->setPosition(ccp(50, screenSize.height - 70));
    p1Name->setPosition(ccp(70, screenSize.height - 120));
    p1Castle->setPosition(ccp(50, screenSize.height - 140));
    p1Wall->setPosition(ccp(50, screenSize.height - 160));
    
    p2Magic->setPosition(ccp(screenSize.width - 90, screenSize.height - 30));
    p2Gems->setPosition(ccp(screenSize.width - 50, screenSize.height - 70));
    p2Name->setPosition(ccp(screenSize.width - 70, screenSize.height - 120));
    p2Castle->setPosition(ccp(screenSize.width - 50, screenSize.height - 140));
    p2Wall->setPosition(ccp(screenSize.width - 50, screenSize.height - 160));
    
    
    // initialize game values
    this->currentPlayerTurn = true;
    
    // add a "close" icon to exit the progress. it's an autorelease object
    
    CCMenuItemImage *turnButton = CCMenuItemImage::create("CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this, menu_selector(Game::nextTurn));
    
    // position the sprite on the center of the screen
    turnButton->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(turnButton, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    // add all elements to the layer
    this->addChild(bgGame, 0);
    
    this->addChild(p1Magic, 1);
    this->addChild(p1Gems, 1);
    this->addChild(p1Name, 1);
    this->addChild(p1Castle, 1);
    this->addChild(p1Wall, 1);
    
    this->addChild(p2Magic, 1);
    this->addChild(p2Gems, 1);
    this->addChild(p2Name, 1);
    this->addChild(p2Castle, 1);
    this->addChild(p2Wall, 1);
    this->schedule(schedule_selector(Game::update));
    return true;
}

void    Game::update(float dt)
{
    CCString pMagicStr =   *CCString::createWithFormat("%d", this->p1->getMagic());
    CCString pGemsStr  =   *CCString::createWithFormat("%d", this->p1->getCrystals());
    CCString comMagicStr   =   *CCString::createWithFormat("%d", this->p2->getMagic());
    CCString comGemsStr    =   *CCString::createWithFormat("%d", this->p2->getCrystals());
    CCString p1CastleStr    =   *CCString::createWithFormat("%d", this->p1->getCastle());
    CCString p1WallStr  =   *CCString::createWithFormat("%d", this->p1->getWall());
    CCString p2CastleStr    =   *CCString::createWithFormat("%d", this->p2->getCastle());
    CCString p2WallStr  =   *CCString::createWithFormat("%d", this->p2->getWall());

    this->p1Magic->setString(pMagicStr.getCString());
    this->p1Gems->setString(pGemsStr.getCString());
    this->p1Castle->setString(p1CastleStr.getCString());
    this->p1Wall->setString(p1WallStr.getCString());
    this->p2Magic->setString(comMagicStr.getCString());
    this->p2Gems->setString(comGemsStr.getCString());
    this->p2Castle->setString(p2CastleStr.getCString());
    this->p2Wall->setString(p2WallStr.getCString());
}

void    Game::switchTurn(bool extra)
{
    this->turn++;
    printf("%d", this->p1->getCrystals());
    if (!extra)
    {
        currentPlayerTurn = !currentPlayerTurn;
    }
    this->startNewTurn(currentPlayerTurn ? p1 : p2);
}

void    Game::startNewTurn(Player *p) {
    p->handleNewTurn();
}

void    Game::nextTurn(CCObject *pSend)
{
    this->switchTurn(false);
     /*
     this->p1->newTurn();
     this->p2->newTurn();
     printf("%d", this->turn);
    */
}