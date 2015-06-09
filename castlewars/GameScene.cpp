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

CCScene* GameScene::createScene()
{
    //GameScene::IMFirst = playFirst;
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    CCLayer *layer = GameScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void    GameScene::cardClick(CCObject *pSend)
{
    if (p1->isLocked()) printf("p1 locked !!!\n");
    if (p1->isLocked()) return;

    CCMenuItem* pMenuItem = (CCMenuItem *)(pSend);
    int tag = (int) pMenuItem->getTag();
    
    CCArray    *effectsArray = NULL;
    
    r = this->p1->play(tag - 1);
    if (r.success) {
        effectsArray = this->applyCardEffects(p1, p2);
        if (this->online) this->netLog->sendPlayResult(r);
    }
    else return;
    
    CCSprite    *cardSprite = CCSprite::create(p1->getCard(tag - 1)->getImage());
    
    // Move the card from the left to the center of the screen
    cardSprite->setPosition(ccp(screenSize.width / 2 + (150 * (tag - 3)), 160));
    cardSprite->setScale(0.65);
    
    this->addChild(cardSprite, 2);
    
    CCFiniteTimeAction  *moveToTop = CCMoveTo::create(1, ccp(screenSize.width / 2,
                                                               screenSize.height * 2));
    CCFiniteTimeAction *endTurn = CCCallFuncN::create(this, callfuncN_selector(GameScene::endTurn));
    
    
    CCArray     *actions = CCArray::createWithObject(moveToTop);
    actions->addObjectsFromArray(effectsArray);
    actions->addObject(endTurn);
    
    CCAction    *moveCard = CCSequence::create(actions);
    
    cardSprite->stopAllActions();
    cardSprite->runAction(moveCard);
    
    
    this->popCardMenuItem(tag);
    this->addCardMenuItem();

    
    //this->endTurn();
}

void    GameScene::cardDiscardButton(CCObject *pSend)
{
    if (this->p1->isLocked()) return;
    
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSend);
    int tag = (int)pMenuItem->getTag();
    
    p1->addGems(this->p1->getCard(tag - 1)->getCost());
    if (this->online) this->netLog->sendDiscardResult(this->p1->getCard(tag - 1)->getCost());

    this->popCardMenuItem(tag);
    this->addCardMenuItem();
    
    
    this->removeChild(pMenuItem, true);
    this->endTurn();
}

void	GameScene::startExplosion(CCPoint pos)
{
    CCParticleExplosion*    explosion = SRes::getInstance().getExplosion(pos);
    
    this->addChild(explosion, 3);
}

void    GameScene::removeGameScene()
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

bool    GameScene::init()
{
    CCLOG("INIT CALLED");
	this->screenSize = CCDirector::sharedDirector()->getWinSize();
    
    this->p1 = new Player("Player", Player::HUMAN);
    if (SRes::getInstance().onlinePlay) {
        this->p2 = new Player("Opponent", Player::HUMAN);
        this->online = true;
        this->netLog = NetworkLogicManager::getInstance().getNetLog();
    }
    else this->p2 = new Player("CPU", Player::COMPUTER);

    this->extraTurn = false;
    
    this->core = new AICore(AICore::EASY);
    
    this->createGameScene(screenSize);
    
    for (int i = 0; i < 5; i++) {
        p1->draw();
        p2->draw();
    }
    
    // initialize game values
    turn = 0;
    bool p1First = SRes::getInstance().playFirst;
    this->currentPlayer = p1First ? p1 : p2;
    this->currentOpponent = p1First ? p2 : p1;
    this->newTurn = true;
    if (p1First) {
        this->p1->unlock();
        this->p2->lock();
    } else {
        this->p2->unlock();
        this->p1->lock();
    }
    
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
    
    this->schedule(schedule_selector(GameScene::update));
    this->running = true;
    
    SRes::getInstance().playSound(SRes::BGM_GAME);
    
    return true;
}

void    GameScene::createGameScene(CCSize screenSize) {
    
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
    this->p1Name            =   CCLabelTTF::create(this->p1->getName(), "MagicFont", 22,
                                                   CCSizeMake(245, 32), kCCTextAlignmentCenter);
    this->p2Name            =   CCLabelTTF::create(this->p2->getName(), "MagicFont", 22,
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

CCMenuItemImage *GameScene::createButton(const char *plain, const char *focus, int tag,
                                    int posX, int posY, float scale,
                                    SEL_MenuHandler callBack) {
    CCMenuItemImage *btn = CCMenuItemImage::create(plain, focus, this, callBack);
    btn->setScale(scale);
    btn->setTag(tag);
    btn->setPosition(ccp(posX, posY));
    
    return btn;
}

CCMenuItemImage *GameScene::createButtonFromCard(Card *card, int tag)
{
    return createButton(card->getImage(), card->getImage(), tag,
                        screenSize.width / 2 + (150 * (tag - 3)), 160, .5, menu_selector(GameScene::cardClick));
}

CCMenuItemImage *GameScene::createDiscardButton(int tag)
{
    return createButton("btnBG.png", "btnBG.png", tag,
                        screenSize.width / 2 + (150 * (tag - 3)), 30, .5, menu_selector(GameScene::cardDiscardButton));
}

void    GameScene::update(float dt)
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
    
    netLog->run();
    
    if (this->online) {
        netLog->run();
        if (!this->p1->isLocked()) return;
        switch (this->netLog->lastEvent) {
            case EVENT_NEW_MSG:
                CCLOG("New message !");
                this->onlinePlay();
                break;
            default:
                break;
        }
    }
    
}

void    GameScene::onlinePlay() {
    r = this->netLog->getResultFromQueue();

    if (r.success) CCLOG("Playing card ... SUCCESS :D");
    else CCLOG("Playing card ... FAILURE D:");
    
    if (!r.success) return;
    
    CCArray *effects = this->applyCardEffects(p2, p1);
    
    // REPLQCE THIS ZITH IMAGE GOT FROM R
    CCSprite    *cardSprite = SRes::getInstance().getSprite(r.cardID);
    
    // Move the card from the right to the center of the screen
    cardSprite->setPosition(ccp(screenSize.width + cardSprite->getScaleX(), screenSize.height / 3 * 2));
    cardSprite->setScale(0.65);
    
    this->addChild(cardSprite, 2);
    
    
    CCFiniteTimeAction  *moveToScreen = CCMoveTo::create(0.5, ccp(screenSize.width / 4 * 3 + 10,
                                                                  screenSize.height / 3 * 2));
    CCFiniteTimeAction  *delay = CCDelayTime::create(1);
    CCFiniteTimeAction  *moveToTop = CCMoveTo::create(0.5, ccp(screenSize.width / 2,
                                                               screenSize.height * 2));
    CCFiniteTimeAction *endTurn = CCCallFuncN::create(this, callfuncN_selector(GameScene::endTurn));
    
    
    CCArray *actions = CCArray::createWithObject(moveToScreen);
    actions->addObjectsFromArray(effects);
    actions->addObject(moveToTop);
    actions->addObject(endTurn);
    
    
    CCAction    *moveCard = CCSequence::create(actions);
    
    cardSprite->stopAllActions();
    cardSprite->runAction(moveCard);
}

void    GameScene::popCardMenuItem(int position) {
    this->cardsMenu->removeChildByTag(position, true);
    this->p1->discard(position - 1);
}

void    GameScene::addCardMenuItem() {
    int pos = this->p1->draw();
    this->cardsMenu->addChild(this->createButtonFromCard(this->p1->getCard(pos), pos + 1));
}

void    GameScene::startTurn()
{
    printf("\nStarting %s turn. Facing %s.\n", currentPlayer->getName(), currentOpponent->getName());
    this->turn++;
    currentPlayer->startTurn();
    if (currentPlayer->getType() == Player::COMPUTER) this->computerTurn();
}

void    GameScene::endTurn()
{
    printf("Ending %s turn\n", currentPlayer->getName());
    this->currentPlayer->endTurn();
    if (!this->extraTurn) {
        currentPlayer = (currentPlayer == p1 ? p2 : p1);
        currentOpponent = (currentPlayer == p1 ? p2 : p1);
    }
    this->checkGameOver();
    this->extraTurn = false;
    this->newTurn = true;
}

void    GameScene::checkGameOver() {
    if (this->p1->getCastle() >= 30 || this->p2->getCastle() <= 0) this->gameOver(true);
    else if (this->p1->getCastle() <= 0 || this->p2->getCastle() >= 30) this->gameOver(false);
}

void GameScene::gameOver(bool win)
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

void GameScene::computerDiscard(Card *card, int pos)
{
    p2->addGems(card->getCost());
    p2->discard(pos);
    p2->draw();
    endTurn();
}

void    GameScene::computerPlay(int pos, CCArray *anims)
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
    CCFiniteTimeAction *endTurn = CCCallFuncN::create(this, callfuncN_selector(GameScene::endTurn));

    
    CCArray *actions = CCArray::createWithObject(moveToScreen);
    actions->addObjectsFromArray(anims);
    actions->addObject(moveToTop);
    actions->addObject(endTurn);

    
    CCAction    *moveCard = CCSequence::create(actions);
    
    cardSprite->stopAllActions();
    cardSprite->runAction(moveCard);
}

void    GameScene::computerTurn()
{
    AIReport report = this->core->getBestMove(p2->hand, p2, p1);
    
    r = this->p2->play(report.bestMovePosition);
    CCArray *effects = NULL;
    if (r.success) effects = this->applyCardEffects(p2, p1);
    if (effects != NULL) this->computerPlay(report.bestMovePosition, effects);
    p2->discard(report.bestMovePosition);
    this->p2->draw();
}


CCArray    *GameScene::applyCardEffects(Player *current, Player *opp) {
    CCArray *effectArray = CCArray::create();
    
    this->extraTurn = r.extraTurn;
    
    if (r.pGemMod != 0) {
        effectArray->addObject(CCCallFuncN::create(this, callfuncN_selector(GameScene::applyPGemEffect)));
        effectArray->addObject(CCDelayTime::create(1));
    }

    if (r.pMagMod != 0) {
        effectArray->addObject(CCCallFuncN::create(this, callfuncN_selector(GameScene::applyPMagicEffect)));
        effectArray->addObject(CCDelayTime::create(1));
    }

    if (r.pCastleMod != 0) {
        effectArray->addObject(CCCallFuncN::create(this, callfuncN_selector(GameScene::applyPCastleEffect)));
        effectArray->addObject(CCDelayTime::create(1));
    }

    if (r.pWallMod != 0) {
        effectArray->addObject(CCCallFuncN::create(this, callfuncN_selector(GameScene::applyPWallEffect)));
        effectArray->addObject(CCDelayTime::create(1));
    }
    
    if (r.oppGemMod != 0) {
        effectArray->addObject(CCCallFuncN::create(this, callfuncN_selector(GameScene::applyOGemEffect)));
        effectArray->addObject(CCDelayTime::create(1));
    }

    if (r.oppMagMod != 0) {
        effectArray->addObject(CCCallFuncN::create(this, callfuncN_selector(GameScene::applyOMagicEffect)));
        effectArray->addObject(CCDelayTime::create(1));
    }

    if (r.oppCastleMod != 0) {
        effectArray->addObject(CCCallFuncN::create(this, callfuncN_selector(GameScene::applyOCastleEffect)));
        effectArray->addObject(CCDelayTime::create(1));
    }
    
    if (r.oppWallMod != 0) {
        effectArray->addObject(CCCallFuncN::create(this, callfuncN_selector(GameScene::applyOWallEffect)));
        effectArray->addObject(CCDelayTime::create(1));
    }
    
    return effectArray;
}

void    GameScene::applyPGemEffect() {
    if (r.pGemMod == 0) return;
    this->currentPlayer->addGems(r.pGemMod);
    SRes::getInstance().playSound(r.pGemMod > 0 ? SRes::GEM_UP : SRes::GEM_DOWN);

    CCPoint pos = SRes::getInstance().getPoint(SRes::CCP_GEM,
                                               this->currentPlayer->getType() == Player::HUMAN);
    this->startExplosion(pos);
}

void    GameScene::applyPMagicEffect() {
    if (r.pMagMod == 0) return;
    this->currentPlayer->addMagic(r.pMagMod);
    SRes::getInstance().playSound(r.pMagMod > 0 ? SRes::MAGIC_UP : SRes::MAGIC_DOWN);
    
    CCPoint pos = SRes::getInstance().getPoint(SRes::CCP_MAGIC,
                                               this->currentPlayer->getType() == Player::HUMAN);
    this->startExplosion(pos);
}

void    GameScene::applyPCastleEffect() {
    if (r.pCastleMod == 0) return;
    if (r.pCastleMod >= 0) this->currentPlayer->addCastle(r.pCastleMod);
    else Card::damageCastle(this->currentPlayer, -r.pCastleMod);
    SRes::getInstance().playSound(r.pCastleMod > 0 ? SRes::CASTLE_UP : SRes::CASTLE_DOWN);
    
    CCPoint pos = SRes::getInstance().getPoint(SRes::CCP_CASTLE,
                                               this->currentPlayer->getType() == Player::HUMAN);
    this->startExplosion(pos);
}

void    GameScene::applyPWallEffect() {
    if (r.pWallMod == 0) return;
    if (r.pWallMod >= 0) this->currentPlayer->addWall(r.pWallMod);
    else Card::damage(this->currentPlayer, -r.pWallMod);
    SRes::getInstance().playSound(r.pWallMod > 0 ? SRes::WALL_UP : SRes::WALL_DOWN);
    
    CCPoint pos = SRes::getInstance().getPoint(SRes::CCP_WALL,
                                               this->currentPlayer->getType() == Player::HUMAN);
    this->startExplosion(pos);
}

void    GameScene::applyOGemEffect() {
    if (r.oppGemMod == 0) return;
    this->currentOpponent->addGems(r.oppGemMod);
    SRes::getInstance().playSound(r.oppGemMod > 0 ? SRes::GEM_UP : SRes::GEM_DOWN);
    
    CCPoint pos = SRes::getInstance().getPoint(SRes::CCP_GEM,
                                               this->currentPlayer->getType() == Player::COMPUTER);
    this->startExplosion(pos);
}

void    GameScene::applyOMagicEffect() {
    if (r.oppMagMod == 0) return;
    this->currentOpponent->addMagic(r.oppMagMod);
    SRes::getInstance().playSound(r.oppMagMod > 0 ? SRes::MAGIC_UP : SRes::MAGIC_DOWN);
    
    CCPoint pos = SRes::getInstance().getPoint(SRes::CCP_MAGIC,
                                               this->currentPlayer->getType() == Player::COMPUTER);
    this->startExplosion(pos);
}

void    GameScene::applyOCastleEffect() {
    if (r.oppCastleMod == 0) return;
    if (r.oppCastleMod >= 0) this->currentOpponent->addCastle(r.oppCastleMod);
    else Card::damageCastle(this->currentOpponent, -r.oppCastleMod);
    SRes::getInstance().playSound(r.oppCastleMod > 0 ? SRes::CASTLE_UP : SRes::CASTLE_DOWN);
    
    CCPoint pos = SRes::getInstance().getPoint(SRes::CCP_CASTLE,
                                               this->currentPlayer->getType() == Player::COMPUTER);
    this->startExplosion(pos);
}

void    GameScene::applyOWallEffect() {
    if (r.oppWallMod == 0) return;
    if (r.oppWallMod >= 0) this->currentOpponent->addWall(r.oppWallMod);
    else Card::damage(this->currentOpponent, -r.oppWallMod);
    SRes::getInstance().playSound(r.oppWallMod > 0 ? SRes::WALL_UP : SRes::WALL_DOWN);
    
    CCPoint pos = SRes::getInstance().getPoint(SRes::CCP_WALL,
                                               this->currentPlayer->getType() == Player::COMPUTER);
    this->startExplosion(pos);
}