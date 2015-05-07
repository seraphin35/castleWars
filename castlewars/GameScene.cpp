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

void    Game::cardClick(CCObject *pSend)
{
    if (p1->isLocked()) printf("p1 locked !!!\n");
    if (p1->isLocked()) return;

    CCMenuItem* pMenuItem = (CCMenuItem *)(pSend);
    int tag = (int) pMenuItem->getTag();
    
    SRes::playResults results = this->p1->play(tag - 1);
    if (results.success) this->applyCardEffects(p1, p2, results);
    else return;
    
    CCSprite    *cardSprite = CCSprite::create(p1->getCard(tag - 1)->getImage());
    
    // Move the card from the left to the center of the screen
    cardSprite->setPosition(ccp(screenSize.width / 2 + (150 * (tag - 3)), 160));
    cardSprite->setScale(0.65);
    
    this->addChild(cardSprite, 2);
    
    CCFiniteTimeAction  *moveToTop = CCMoveTo::create(1, ccp(screenSize.width / 2,
                                                               screenSize.height * 2));
    CCFiniteTimeAction *endTurn = CCCallFuncN::create(this, callfuncN_selector(Game::endTurn));
    
    CCAction    *moveCard = CCSequence::create(moveToTop, endTurn, NULL, NULL, NULL);
    
    cardSprite->stopAllActions();
    cardSprite->runAction(moveCard);
    
    
    this->popCardMenuItem(tag);
    this->addCardMenuItem();

    
    //this->endTurn();
}

void    Game::applyCardEffects(Player *current, Player *opp, SRes::playResults r) {
    this->extraTurn = r.extraTurn;
    current->addGems(r.pGemMod);
    current->addMagic(r.pMagMod);
    if (r.pCastleMod >= 0) current->addCastle(r.pCastleMod);
    else Card::damageCastle(current, -r.pCastleMod);
    if (r.pWallMod >= 0) current->addWall(r.pWallMod);
    else Card::damage(current, -r.pWallMod);
    opp->addGems(r.oppGemMod);
    opp->addMagic(r.oppMagMod);
    if (r.oppCastleMod >= 0) opp->addCastle(r.oppCastleMod);
    else Card::damageCastle(opp, -r.oppCastleMod);
    if (r.oppWallMod >= 0) opp->addWall(r.oppWallMod);
    else Card::damage(opp, -r.oppWallMod);
    
    CCPoint pos = ccp(screenSize.width / 2 - 135, screenSize.height / 2 + 6);
    this->startExplosion(pos);
}

void    Game::cardDiscardButton(CCObject *pSend)
{
    if (this->p1->isLocked()) return;
    
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSend);
    int tag = (int)pMenuItem->getTag();
    
    p1->addGems(this->p1->getCard(tag - 1)->getCost());

    this->popCardMenuItem(tag);
    this->addCardMenuItem();
    
    this->removeChild(pMenuItem, true);
    this->endTurn();
}

void	Game::startExplosion(CCPoint pos)
{
    CCTexture2D*            texture = CCSprite::create("star.png")->getTexture();
    CCParticleExplosion*    explosion = new CCParticleExplosion();

    explosion->initWithTotalParticles(30);
    explosion->setTexture(texture);
    explosion->setPosition(pos);
    explosion->setDuration(0.01f);
    explosion->setSpeed(200);
    explosion->setGravity(ccp(0, -250));
    explosion->setAngle(90);
    explosion->setAngleVar(10);
    explosion->setStartSize(20);
    explosion->setEndSize(0);
    explosion->setLife(1.0f);
    explosion->setLifeVar(1.0f);
    explosion->setEmissionRate(200);
    explosion->setAutoRemoveOnFinish(true);
    
    this->addChild(explosion, 3);
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
	this->screenSize = CCDirector::sharedDirector()->getWinSize();
    
    this->p1 = new Player("Player", Player::HUMAN);
    this->p2 = new Player("CPU", Player::COMPUTER);
    
    this->extraTurn = false;
    
    this->core = new AICore(AICore::MEDIUM);
    
    this->createGameScene(screenSize);
    
    for (int i = 0; i < 5; i++) {
        p1->draw();
        p2->draw();
    }
    
    // initialize game values
    turn = 0;
    this->currentPlayer = p1;
    this->newTurn = true;
    this->p1->unlock();
    this->p2->lock();
    
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
    this->running = true;
    
    SRes::getInstance().playSound(SRes::BGM_GAME);
    
    return true;
}

void    Game::createGameScene(CCSize screenSize) {
    
    // Background
    this->bgGame = CCSprite::create("gameBG.png");
    this->bgGame->setScaleX(screenSize.width / bgGame->getContentSize().width);
    this->bgGame->setScaleY(screenSize.height / bgGame->getContentSize().height);
    this->bgGame->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->bgGame->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(this->bgGame);
    
    // Values strings
    CCString pMagicStr      =   *CCString::createWithFormat("%d", this->p1->getMagic());
    this->p1Magic           =   CCLabelTTF::create(pMagicStr.getCString(), "MagicFont", 22,
                                                   CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString pGemsStr       =   *CCString::createWithFormat("%d", this->p1->getGems());
    this->p1Gems            =   CCLabelTTF::create(pGemsStr.getCString(), "MagicFont", 20,
                                                   CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p2MagicStr     =   *CCString::createWithFormat("%d", this->p2->getMagic());
    this->p2Magic           =   CCLabelTTF::create(p2MagicStr.getCString(), "MagicFont", 22,
                                                   CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p2GemsStr      =   *CCString::createWithFormat("%d", this->p2->getGems());
    this->p2Gems            =  CCLabelTTF::create(p2GemsStr.getCString(), "MagicFont", 20,
                                                  CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p1CastleStr    =   *CCString::createWithFormat("%d", this->p1->getCastle());
    this->p1Castle          =   CCLabelTTF::create(p1CastleStr.getCString(), "MagicFont", 18,
                                                   CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p1WallStr      =   *CCString::createWithFormat("%d", this->p1->getWall());
    this->p1Wall            =   CCLabelTTF::create(p1WallStr.getCString(), "MagicFont", 18,
                                                   CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p2CastleStr    =   *CCString::createWithFormat("%d", this->p2->getCastle());
    this->p2Castle          =   CCLabelTTF::create(p2CastleStr.getCString(), "MagicFont", 18,
                                                   CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCString p2WallStr      =   *CCString::createWithFormat("%d", this->p2->getWall());
    this->p2Wall            =   CCLabelTTF::create(p2WallStr.getCString(), "MagicFont", 18,
                                                   CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p1Name            =   CCLabelTTF::create("Player 1", "MagicFont", 22,
                                                   CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p2Name            =   CCLabelTTF::create("Computer", "MagicFont", 22,
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
    if (!running) return;

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
    
    if (this->newTurn) {
        this->newTurn = false;
        this->startTurn();
    }
}

void    Game::popCardMenuItem(int position) {
    this->cardsMenu->removeChildByTag(position, true);
    this->p1->discard(position - 1);
}

void    Game::addCardMenuItem() {
    int pos = this->p1->draw();
    this->cardsMenu->addChild(this->createButtonFromCard(this->p1->getCard(pos), pos + 1));
}

void    Game::startTurn()
{
    printf("\nStarting %s turn\n", currentPlayer->getName());
    this->turn++;
    currentPlayer->startTurn();
    if (currentPlayer->getType() == Player::COMPUTER) this->computerTurn();
}

void    Game::endTurn()
{
    printf("Ending %s turn\n", currentPlayer->getName());
    this->currentPlayer->endTurn();
    if (!this->extraTurn) currentPlayer = (currentPlayer == p1 ? p2 : p1);
    this->checkGameOver();
    this->extraTurn = false;
    this->newTurn = true;
}

void    Game::checkGameOver() {
    if (this->p1->getCastle() >= 30 || this->p2->getCastle() <= 0) this->gameOver(true);
    else if (this->p1->getCastle() <= 0 || this->p2->getCastle() >= 30) this->gameOver(false);
}

void Game::gameOver(bool win)
{
    printf("Player %s\n", win ? "won." : "lost.");
    
    this->running = false;
    SRes::getInstance().setEndGameInfos(this->turn,
                                        this->p1->getCastle(),
                                        this->p2->getCastle(),
                                        this->p1->getWall(),
                                        this->p2->getWall(),
                                        win);
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeDown::create(0.8, GameOver::createScene()));
}




void Game::computerDiscard(Card *card, int pos)
{
    p2->addGems(card->getCost());
    p2->discard(pos);
    p2->draw();
    endTurn();
}

void    Game::computerPlay(int pos)
{
    CCSprite    *cardSprite = CCSprite::create(p2->getCard(pos)->getImage());
    
    // Move the card from the right to the center of the screen
    cardSprite->setPosition(ccp(screenSize.width + cardSprite->getScaleX(), screenSize.height / 3 * 2));
    cardSprite->setScale(0.65);
    
    this->addChild(cardSprite, 2);
    
    CCFiniteTimeAction  *moveToScreen = CCMoveTo::create(0.5, ccp(screenSize.width / 4 * 3 + 10,
                                                                  screenSize.height / 3 * 2));
    CCFiniteTimeAction  *delay = CCDelayTime::create(1);
    CCFiniteTimeAction  *moveToTop = CCMoveTo::create(0.5, ccp(screenSize.width / 2,
                                                               screenSize.height * 2));
    CCFiniteTimeAction *endTurn = CCCallFuncN::create(this, callfuncN_selector(Game::endTurn));
    
    CCAction    *moveCard = CCSequence::create(moveToScreen, delay, moveToTop, endTurn, NULL, NULL, NULL);
    
    cardSprite->stopAllActions();
    cardSprite->runAction(moveCard);
    
    /*
    ptrfunc fu;
    
    p2->removeGems(p2->getCard(pos)->getCost());
    
    fu = p2->getCard(pos)->getEffect();
    this->extraTurn = fu(p2, p1);
    p2->discard(pos);
    this->p2->draw();
*/

    //this->endTurn();
}

void    Game::computerTurn()
{
    AIReport report = this->core->getBestMove(p2->hand, p2, p1);
    
    SRes::playResults results = this->p2->play(report.bestMovePosition);
    if (results.success) this->applyCardEffects(p2, p1, results);
    this->computerPlay(report.bestMovePosition);
    p2->discard(report.bestMovePosition);
    this->p2->draw();
    
    /*
    Card        *hand[5];
    hand[0] = p2->getCard(0);
    hand[1] = p2->getCard(1);
    hand[2] = p2->getCard(2);
    hand[3] = p2->getCard(3);
    hand[4] = p2->getCard(4);
    bool hasPlayed = false;
    
    // Choose the card to play or discard
    for (int i = 0; i < 5; i++)
    {
        if (hand[i]->getCost() <= p2->getGems())
        {
            computerPlay(hand[i], i);
            hasPlayed = true;
            break;
        }
    }
    if (!hasPlayed) {
        int to_discard = 0;
        for (int i = 0; i < 5; i++) {
            if (hand[i]->getCost() > hand[to_discard]->getCost() || i == 4)
                to_discard = i;
        }
        computerDiscard(hand[to_discard], to_discard);
    }
     */
}
