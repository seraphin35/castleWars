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
#include "SRes.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"
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

void Game::gameOver(bool hasWon)
{
    removeGameScene();

    this->gameEnd = true;

    SRes::getInstance().setEndGameInfos(this->turn,
                                        this->p1->getCastle(),
                                        this->p2->getCastle(),
                                        this->p1->getWall(),
                                        this->p2->getWall(),
                                        hasWon);
    CCScene *gameOverScene = GameOver::createScene();
    gameOverScene->init();

    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeDown::create(0.8, gameOverScene));

}

void    Game::cardClick(CCObject *pSend)
{
    ptrfunc fu;
    
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSend);
    int tag = (int)pMenuItem->getTag();
    
    if (this->p1->getCard(tag - 1)->getCost() <= this->p1->getGems())
    {
    fu = this->p1->getCard(tag - 1)->getEffect();
    
    p1->removeGems(this->p1->getCard(tag - 1)->getCost());
    
    bool extra = fu(p1, p2);
    this->popCardMenuItem(tag);
    this->addCardMenuItem();
    
    if (this->p1->getCastle() >= 30 || this->p2->getCastle() <= 0)
    {
        this->removeChild(pMenuItem, true);
        gameOver(true);
        printf("Win");
    }
    else if (this->p1->getCastle() <= 0 || this->p2->getCastle() >= 30)
    {
        gameOver(false);
        printf("Lose");
    }
    else
        this->switchTurn(extra);
    }
}

void    Game::cardDiscardButton(CCObject *pSend)
{
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSend);
    int tag = (int)pMenuItem->getTag();
    
    p1->addGems(this->p1->getCard(tag - 1)->getCost());

    this->popCardMenuItem(tag);
    this->addCardMenuItem();
    
    this->removeChild(pMenuItem, true);
    this->switchTurn(false);
}

void    Game::removeGameScene()
{
    this->removeChild(this->bgGame, true);
    //this->removeChild(this->cardsMenu, true);
    
    // remove p1 values
    this->removeChild(this->p1Magic, true);
    this->removeChild(this->p1Gems, true);
    this->removeChild(this->p1Name, true);
    this->removeChild(this->p1Castle, true);
    this->removeChild(this->p1Wall, true);
    
    // remove p2 values
    this->removeChild(this->p2Magic, true);
    this->removeChild(this->p2Gems, true);
    this->removeChild(this->p2Name, true);
    this->removeChild(this->p2Castle, true);
    this->removeChild(this->p2Wall, true);
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
    turn = 0;
    this->currentPlayerTurn = true;
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *bCard1 = createButtonFromCard(this->p1->getCard(0), 1);
    CCMenuItemImage *bCard2 = createButtonFromCard(this->p1->getCard(1), 2);
    CCMenuItemImage *bCard3 = createButtonFromCard(this->p1->getCard(2), 3);
    CCMenuItemImage *bCard4 = createButtonFromCard(this->p1->getCard(3), 4);
    CCMenuItemImage *bCard5 = createButtonFromCard(this->p1->getCard(4), 5);
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *discard1 = createDiscardButton(1);
    CCMenuItemImage *discard2 = createDiscardButton(2);
    CCMenuItemImage *discard3 = createDiscardButton(3);
    CCMenuItemImage *discard4 = createDiscardButton(4);
    CCMenuItemImage *discard5 = createDiscardButton(5);
    
    CCLabelTTF *dTxt1 = CCLabelTTF::create("Discard", "MagicFont", 16,
                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCLabelTTF *dTxt2 = CCLabelTTF::create("Discard", "MagicFont", 16,
                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCLabelTTF *dTxt3 = CCLabelTTF::create("Discard", "MagicFont", 16,
                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCLabelTTF *dTxt4 = CCLabelTTF::create("Discard", "MagicFont", 16,
                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCLabelTTF *dTxt5 = CCLabelTTF::create("Discard", "MagicFont", 16,
                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    
    dTxt1->setPosition(ccp(screenSize.width / 2 + (150 * (1 - 3)), 30));
    dTxt2->setPosition(ccp(screenSize.width / 2 + (150 * (2 - 3)), 30));
    dTxt3->setPosition(ccp(screenSize.width / 2 + (150 * (3 - 3)), 30));
    dTxt4->setPosition(ccp(screenSize.width / 2 + (150 * (4 - 3)), 30));
    dTxt5->setPosition(ccp(screenSize.width / 2 + (150 * (5 - 3)), 30));

    this->addChild(dTxt1, 2);
    this->addChild(dTxt2, 2);
    this->addChild(dTxt3, 2);
    this->addChild(dTxt4, 2);
    this->addChild(dTxt5, 2);

    // create menu, it's an autorelease object
    this->cardsMenu = CCMenu::create(bCard5, bCard4, bCard3, bCard2, bCard1,
                                     discard1, discard2, discard3, discard4, discard5, NULL);

    this->cardsMenu->setPosition( CCPointZero );
    this->addChild(this->cardsMenu, 1);
    
    this->schedule(schedule_selector(Game::update));
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameBGM.mp3", true);
    
    return true;
}

void    Game::createGameScene(CCSize screenSize) {
    this->gameEnd = false;
    
    // Background
    this->bgGame = CCSprite::create("gameBG.png");
    this->bgGame->setScaleX(screenSize.width / bgGame->getContentSize().width);
    this->bgGame->setScaleY(screenSize.height / bgGame->getContentSize().height);
    this->bgGame->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->bgGame->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(this->bgGame);
    
    // Values strings
    CCString pMagicStr  =   *CCString::createWithFormat("%d", this->p1->getMagic());
    this->p1Magic       =   CCLabelTTF::create(pMagicStr.getCString(), "MagicFont", 22,
                                               CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString pGemsStr   =   *CCString::createWithFormat("%d", this->p1->getGems());
    this->p1Gems        =   CCLabelTTF::create(pGemsStr.getCString(), "MagicFont", 20,
                                               CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p2MagicStr =   *CCString::createWithFormat("%d", this->p2->getMagic());
    this->p2Magic       =   CCLabelTTF::create(p2MagicStr.getCString(), "MagicFont", 22,
                                               CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p2GemsStr  =   *CCString::createWithFormat("%d", this->p2->getGems());
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
    
    // setPosition for p1
    p1Magic->setPosition(ccp(105, screenSize.height - 30));
    p1Gems->setPosition(ccp(53, screenSize.height - 67));
    p1Name->setPosition(ccp(70, screenSize.height - 110));
    p1Castle->setPosition(ccp(screenSize.width / 2 - 135, screenSize.height / 2 + 6));
    p1Wall->setPosition(ccp(screenSize.width / 2 - 45, screenSize.height / 2 + 6));
    
    // setPosition for p2
    p2Magic->setPosition(ccp(screenSize.width - 82, screenSize.height - 32));
    p2Gems->setPosition(ccp(screenSize.width - 47, screenSize.height - 67));
    p2Name->setPosition(ccp(screenSize.width - 70, screenSize.height - 110));
    p2Castle->setPosition(ccp(screenSize.width / 2 + 135, screenSize.height / 2 + 6));
    p2Wall->setPosition(ccp(screenSize.width / 2 + 47, screenSize.height / 2 + 6));
    
    // display p1 values
    this->addChild(p1Magic, 1);
    this->addChild(p1Gems, 1);
    this->addChild(p1Name, 1);
    this->addChild(p1Castle, 1);
    this->addChild(p1Wall, 1);
    
    // display p2 values
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

CCMenuItemImage *Game::createButtonFromCard(Card *card, int tag)
{
    return createButton(card->getImage(), card->getImage(), tag,
                        screenSize.width / 2 + (150 * (tag - 3)), 160, .5, menu_selector(Game::cardClick));
}

CCMenuItemImage *Game::createDiscardButton(int tag)
{
    return createButton("btnBG.png", "btnBG.png", tag,
                        screenSize.width / 2 + (150 * (tag - 3)), 30, .5, menu_selector(Game::cardDiscardButton));
}

void    Game::update(float dt)
{
    if (!gameEnd)
    {
        CCString pMagicStr      =   *CCString::createWithFormat("%d", this->p1->getMagic());
        CCString pGemsStr       =   *CCString::createWithFormat("%d", this->p1->getGems());
        CCString p2MagicStr     =   *CCString::createWithFormat("%d", this->p2->getMagic());
        CCString p2GemsStr      =   *CCString::createWithFormat("%d", this->p2->getGems());
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
}

void    Game::popCardMenuItem(int position) {
    printf("b popCardMebuItem\n");
    this->cardsMenu->removeChildByTag(position, true);
    this->p1->discard(position - 1);
    printf("a popCardMebuItem\n");
}

void    Game::addCardMenuItem() {
    printf("b addCardMebuItem\n");
    int pos = this->p1->draw();
    this->cardsMenu->addChild(this->createButtonFromCard(this->p1->getCard(pos), pos + 1));
    printf("a addCardMebuItem\n");
}

void    Game::switchTurn(bool extra)
{
    this->turn++;
    printf("%d", this->p1->getGems());
    if (!extra)
    {
        currentPlayerTurn = !currentPlayerTurn;
    }
    this->startNewTurn(currentPlayerTurn ? p1 : p2);
}

void    Game::startNewTurn(Player *p)
{
    p->handleNewTurn();
    if (!currentPlayerTurn)
    {
        this->computerTurn();
    }
}

void    Game::computerTurn()
{
    Card        *card       = p2->getCard(0);
    CCSprite    *cardSprite = CCSprite::create(card->getImage());
    
    printf("card moving [%f]", cardSprite->getScaleX());
    
    // Move the card from the right to the center of the screen
    cardSprite->setPosition(ccp(screenSize.width + cardSprite->getScaleX(), screenSize.height / 3 * 2));
    cardSprite->setScale(0.7);
    
    this->addChild(cardSprite, 2);
    
    CCFiniteTimeAction  *moveToCenter = CCMoveTo::create(0.5, ccp(screenSize.width / 2,
                                                                  screenSize.height / 3 * 2));
    CCFiniteTimeAction  *delay = CCDelayTime::create(1);
    CCFiniteTimeAction  *moveToTop = CCMoveTo::create(0.3, ccp(screenSize.width / 2,
                                                               screenSize.height + (cardSprite->getScaleY() * 4)));
    CCFiniteTimeAction *endFun = CCCallFuncN::create(this, callfuncN_selector(Game::cleanSprite));
    CCAction    *moveCard = CCSequence::create(moveToCenter, delay, moveToTop, endFun, NULL);
    
    cardSprite->stopAllActions();
    cardSprite->runAction(moveCard);
    
    p2->discard(0);
    
    ptrfunc fu;
    
    fu = card->getEffect();
    
    bool extra = fu(p2, p1);
    this->p2->draw();
    switchTurn(extra);
}

void    Game::cleanSprite(CCSprite *sprite)
{
    this->removeChild(sprite, true);
}
