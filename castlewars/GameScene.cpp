//
//  GameScene.cpp
//  castlewars
//
//  Created by Guest User on 4/3/15.
//
//

#include "GameScene.h"
#include "cocos2d.h"

bool    Game::init()
{
    // get screen size
	CCSize  screenSize = CCDirector::sharedDirector()->getWinSize();
    
    // create and add game background
    CCSprite* bgGame = CCSprite::create("BackgroundGame.png");
    bgGame->setScaleX(screenSize.width / bgGame->getContentSize().width);
    bgGame->setScaleY(screenSize.height / bgGame->getContentSize().height);
    bgGame->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    
    // Create magic and gems numbers as string
    this->pMagicStr =   *CCString::createWithFormat("%d", this->p1->getMagic());
    this->p1Magic   =   CCLabelTTF::create(pMagicStr.getCString(), "Thonburi", 42,
                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    
    this->pGemsStr  =   *CCString::createWithFormat("%d", this->p1->getMagic());
    this->p1Gems    =   CCLabelTTF::create(pGemsStr.getCString(), "Thonburi", 42,
                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    
    this->comMagicStr   =   *CCString::createWithFormat("%d", this->p1->getMagic());
    this->p2Magic       =   CCLabelTTF::create(comMagicStr.getCString(), "Thonburi", 42,
                                               CCSizeMake(245, 32), kCCTextAlignmentCenter);
    
    this->comGemsStr    =   *CCString::createWithFormat("%d", this->p1->getMagic());
    this->p2Gems        =  CCLabelTTF::create(comGemsStr.getCString(), "Thonburi", 42,
                                              CCSizeMake(245, 32), kCCTextAlignmentCenter);
    
    // create names
    this->p1Name    = CCLabelTTF::create("Player 1", "Helvetica", 30,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p2Name    = CCLabelTTF::create("Computer", "Helvetica", 30,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);

    // set all positions
    bgGame->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    
    p1Magic->setPosition(ccp(50, screenSize.height - 40));
    p1Gems->setPosition(ccp(30, screenSize.height - 80));
    p1Name->setPosition(ccp(30, screenSize.height - 120));
    
    p2Magic->setPosition(ccp(screenSize.width - 50, screenSize.height - 40));
    p2Gems->setPosition(ccp(screenSize.width - 30, screenSize.height - 80));
    p2Name->setPosition(ccp(screenSize.width - 30, screenSize.height - 120));

    // add all elements to the layer
    this->addChild(bgGame, 0);

    this->addChild(p1Magic, 1);
    this->addChild(p1Gems, 1);
    this->addChild(p1Name, 1);
    
    this->addChild(p2Magic, 1);
    this->addChild(p2Gems, 1);
    this->addChild(p2Name, 1);
    
    this->schedule(schedule_selector(Game::update));
    
    // initialize game values
    this->currentPlayerTurn = true;
    
    // add a "close" icon to exit the progress. it's an autorelease object
    this->p1 = new Player();
    this->p2 = new Player();
    
    CCMenuItemImage *turnButton = CCMenuItemImage::create("CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this, menu_selector(Game::nextTurn));
    
    // position the sprite on the center of the screen
    turnButton->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(turnButton, turnButton, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    return true;
}

void    Game::update(float dt)
{
    
}

void    Game::switchTurn(bool extra)
{
    this->turn++;
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
    this->turn += 1;
    /*
     
     this->p1->newTurn();
     this->p2->newTurn();
     printf("%d", this->turn);
     */
}