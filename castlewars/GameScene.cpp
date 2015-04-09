//
//  GameScene.cpp
//  castlewars
//
//  Created by Guest User on 4/3/15.
//
//

#include "GameScene.h"
#include "cocos2d.h"
#include "Card.h"
#include "SimpleAudioEngine.h"
#include <unistd.h>

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

void Game::zob(CCObject *pSend) {
    ptrfunc fu;
    
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSend);
    int tag = (int)pMenuItem->getTag();
    
    fu = this->p1->getCard(tag - 1)->getEffect();
    
    
    bool extra = fu(p1, p2);
    sleep(1);
    this->popCardMenuItem(tag);
    this->addCardMenuItem();
    
    this->switchTurn(extra);
}

bool    Game::init()
{
    // get screen size
	this->screenSize = CCDirector::sharedDirector()->getWinSize();
    
    this->p1 = new Player();
    this->p2 = new Player();

    this->createGameScene(screenSize);

    for (int i = 0; i < 5; i++) {
        p1->draw();
        p2->draw();
    }

    // initialize game values
    this->currentPlayerTurn = true;
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *bCard1 = createButtonFromCard(this->p1->getCard(0), 1);
    CCMenuItemImage *bCard2 = createButtonFromCard(this->p1->getCard(1), 2);
    CCMenuItemImage *bCard3 = createButtonFromCard(this->p1->getCard(2), 3);
    CCMenuItemImage *bCard4 = createButtonFromCard(this->p1->getCard(3), 4);
    CCMenuItemImage *bCard5 = createButtonFromCard(this->p1->getCard(4), 5);
    
    // create menu, it's an autorelease object
    this->cardsMenu = CCMenu::create(bCard5, bCard4, bCard3, bCard2, bCard1, NULL);
    this->cardsMenu->setPosition( CCPointZero );
    this->addChild(this->cardsMenu, 1);

    this->schedule(schedule_selector(Game::update));
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameBGM.mp3", true);
    
    return true;
}

void    Game::createGameScene(CCSize screenSize) {
    
    // Background
    CCSprite* bgGame = CCSprite::create("BackgroundGame.png");
    bgGame->setScaleX(screenSize.width / bgGame->getContentSize().width);
    bgGame->setScaleY(screenSize.height / bgGame->getContentSize().height);
    bgGame->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    bgGame->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(bgGame);
    
    // Values strings
    CCString pMagicStr  =   *CCString::createWithFormat("%d", this->p1->getMagic());
    this->p1Magic       =   CCLabelTTF::create(pMagicStr.getCString(), "MagicFont", 22,
                                               CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString pGemsStr   =   *CCString::createWithFormat("%d", this->p1->getCrystals());
    this->p1Gems        =   CCLabelTTF::create(pGemsStr.getCString(), "MagicFont", 20,
                                               CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p2MagicStr =   *CCString::createWithFormat("%d", this->p2->getMagic());
    this->p2Magic       =   CCLabelTTF::create(p2MagicStr.getCString(), "MagicFont", 22,
                                               CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p2GemsStr  =   *CCString::createWithFormat("%d", this->p2->getCrystals());
    this->p2Gems        =  CCLabelTTF::create(p2GemsStr.getCString(), "MagicFont", 20,
                                              CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p1CastleStr    =   *CCString::createWithFormat("%d", this->p1->getCastle());
    this->p1Castle  = CCLabelTTF::create(p1CastleStr.getCString(), "MagicFont", 18,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p1WallStr      =   *CCString::createWithFormat("%d", this->p1->getWall());
    this->p1Wall    = CCLabelTTF::create(p1WallStr.getCString(), "MagicFont", 18,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p2CastleStr    =   *CCString::createWithFormat("%d", this->p2->getCastle());
    this->p2Castle  = CCLabelTTF::create(p2CastleStr.getCString(), "MagicFont", 18,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p2WallStr      =   *CCString::createWithFormat("%d", this->p2->getWall());
    this->p2Wall    = CCLabelTTF::create(p2WallStr.getCString(), "MagicFont", 18,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p1Name    = CCLabelTTF::create("Player 1", "MagicFont", 22,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p2Name    = CCLabelTTF::create("Computer", "MagicFont", 22,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);
    p1Magic->setPosition(ccp(105, screenSize.height - 30));
    p1Gems->setPosition(ccp(53, screenSize.height - 67));
    p1Name->setPosition(ccp(70, screenSize.height - 110));
    p1Castle->setPosition(ccp(screenSize.width / 2 - 135, screenSize.height / 2 + 6));
    p1Wall->setPosition(ccp(screenSize.width / 2 - 45, screenSize.height / 2 + 6));
    p2Magic->setPosition(ccp(screenSize.width - 82, screenSize.height - 32));
    p2Gems->setPosition(ccp(screenSize.width - 47, screenSize.height - 67));
    p2Name->setPosition(ccp(screenSize.width - 70, screenSize.height - 110));
    p2Castle->setPosition(ccp(screenSize.width / 2 + 135, screenSize.height / 2 + 6));
    p2Wall->setPosition(ccp(screenSize.width / 2 + 47, screenSize.height / 2 + 6));
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
}

CCMenuItemImage *Game::createButton(const char *plain, const char *focus, int tag,
                                 int posX, int posY, float scale,
                                 SEL_MenuHandler callBack) {
    CCMenuItemImage *btn = CCMenuItemImage::create(plain, focus, this, callBack);
    btn->setScale(scale);
    btn->setTag(tag);
    btn->setPosition(ccp(posX, posY));

    return btn;
}

CCMenuItemImage *Game::createButtonFromCard(Card *card, float scale, int tag, int posX, int posY)
{
    return createButton(card->getImage(), card->getImage(), tag,
                        screenSize.width / 2 + (150 * (tag - 3)), 150, .5, menu_selector(Game::zob));
}

void    Game::update(float dt)
{
    CCString pMagicStr      =   *CCString::createWithFormat("%d", this->p1->getMagic());
    CCString pGemsStr       =   *CCString::createWithFormat("%d", this->p1->getCrystals());
    CCString p2MagicStr    =   *CCString::createWithFormat("%d", this->p2->getMagic());
    CCString p2GemsStr     =   *CCString::createWithFormat("%d", this->p2->getCrystals());
    CCString p1CastleStr    =   *CCString::createWithFormat("%d", this->p1->getCastle());
    CCString p1WallStr      =   *CCString::createWithFormat("%d", this->p1->getWall());
    CCString p2CastleStr    =   *CCString::createWithFormat("%d", this->p2->getCastle());
    CCString p2WallStr      =   *CCString::createWithFormat("%d", this->p2->getWall());

    this->p1Magic->setString(pMagicStr.getCString());
    this->p1Gems->setString(pGemsStr.getCString());
    this->p1Castle->setString(p1CastleStr.getCString());
    this->p1Wall->setString(p1WallStr.getCString());
    this->p2Magic->setString(p2MagicStr.getCString());
    this->p2Gems->setString(p2GemsStr.getCString());
    this->p2Castle->setString(p2CastleStr.getCString());
    this->p2Wall->setString(p2WallStr.getCString());
}

void    Game::popCardMenuItem(int position) {
    this->cardsMenu->removeChildByTag(position, true);
    this->p1->discard(position - 1);
}

void    Game::addCardMenuItem() {
    int pos = this->p1->draw();
    this->cardsMenu->addChild(this->createButtonFromCard(this->p1->getCard(pos), pos + 1));
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

