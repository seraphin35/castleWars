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
    
    switch (tag) {
        case 1:
            fu = this->c1->getEffect();
            break;
        case 2:
            fu = this->c2->getEffect();
            break;
        case 3:
            fu = this->c3->getEffect();
            break;
        case 4:
            fu = this->c4->getEffect();
            break;
        case 5:
            fu = this->c5->getEffect();
            break;
            
        default:
            break;
    }
    
    fu(p1, p2);
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
    CCString p1WallStr      =   *CCString::createWithFormat("%d", this->p1->getWall());
    CCString p2CastleStr    =   *CCString::createWithFormat("%d", this->p2->getCastle());
    CCString p2WallStr      =   *CCString::createWithFormat("%d", this->p2->getWall());
    
    this->p1Castle  = CCLabelTTF::create(p1CastleStr.getCString(), "MagicFont", 18,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p1Wall    = CCLabelTTF::create(p1WallStr.getCString(), "MagicFont", 18,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p2Castle  = CCLabelTTF::create(p2CastleStr.getCString(), "MagicFont", 18,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p2Wall    = CCLabelTTF::create(p2WallStr.getCString(), "MagicFont", 18,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);

    this->card1 = CCSprite::create("amethyst_wand.png");
    this->card2 = CCSprite::create("recycled_rainbow.png");
    this->card3 = CCSprite::create("mana_disease.png");
    this->card4 = CCSprite::create("strip_mining.png");
    this->card5 = CCSprite::create("stone_giant.png");
    this->c1 = new Card(&Card::amethystWand, 4, card1);
    this->c2 = new Card(&Card::amethystWand, 4, card2);
    this->c3 = new Card(&Card::amethystWand, 4, card3);
    this->c4 = new Card(&Card::amethystWand, 4, card4);
    this->c5 = new Card(&Card::amethystWand, 4, card5);

    // create names
    this->p1Name    = CCLabelTTF::create("Player 1", "MagicFont", 22,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p2Name    = CCLabelTTF::create("Computer", "MagicFont", 22,
                                         CCSizeMake(245, 32), kCCTextAlignmentCenter);

    // set all positions
    bgGame->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    
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
    
    // initialize game values
    this->currentPlayerTurn = true;
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *turnButton = CCMenuItemImage::create("CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this, menu_selector(Game::nextTurn));

    CCSprite    *card1 = CCSprite::create("amethyst_wand.png");
    card1->setPosition(ccp(screenSize.width / 2 - 300, 150));
    card1->setScale(0.5);
    
    CCSprite    *card2 = CCSprite::create("amethyst_wand.png");
    card2->setPosition(ccp(screenSize.width / 2 - 150, 150));
    card2->setScale(0.5);
    
    CCSprite    *card3 = CCSprite::create("amethyst_wand.png");
    card3->setPosition(ccp(screenSize.width / 2, 150));
    card3->setScale(0.5);
    
    CCSprite    *card4 = CCSprite::create("amethyst_wand.png");
    card4->setPosition(ccp(screenSize.width / 2 + 150, 150));
    card4->setScale(0.5);
    
    CCSprite    *card5 = CCSprite::create("amethyst_wand.png");
    card5->setPosition(ccp(screenSize.width / 2 + 300, 150));
    card5->setScale(0.5);
    
//    CCMenuItemImage *bCard1 = CCMenuItemImage::create("amethyst_wand.png",
//                                                          "recycled_rainbow.png",
//                                                          this, menu_selector(Game::zob));
//    bCard1->setTag(1);
//    CCMenuItemImage *bCard2 = CCMenuItemImage::create("amethyst_wand.png",
//                                                          "recycled_rainbow.png",
//                                                          this, menu_selector(Game::zob));
//    bCard2->setTag(2);
//    CCMenuItemImage *bCard3 = CCMenuItemImage::create("amethyst_wand.png",
//                                                          "recycled_rainbow.png",
//                                                          this, menu_selector(Game::zob));
//    bCard3->setTag(3);
//    CCMenuItemImage *bCard4 = CCMenuItemImage::create("amethyst_wand.png",
//                                                          "recycled_rainbow.png",
//                                                          this, menu_selector(Game::zob));
//    bCard4->setTag(4);
//    CCMenuItemImage *bCard5 = CCMenuItemImage::create("amethyst_wand.png",
//                                                          "recycled_rainbow.png",
//                                                          this, menu_selector(Game::zob));
//    bCard5->setTag(5);
    
    // position the sprite on the center of the screen
    turnButton->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
//    bCard1->setPosition(ccp(150, screenSize.height - 500));
//    bCard2->setPosition(ccp(200, screenSize.height - 500));
//    bCard3->setPosition(ccp(250, screenSize.height - 500));
//    bCard4->setPosition(ccp(300, screenSize.height - 500));
//    bCard5->setPosition(ccp(350, screenSize.height - 500));

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
    
    // This order is important for the display
    this->addChild(card5, 1);
    this->addChild(card4, 1);
    this->addChild(card3, 1);
    this->addChild(card2, 1);
    this->addChild(card1, 1);

    this->schedule(schedule_selector(Game::update));
    return true;
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

