//
//  GameScene.h
//  castlewars
//
//  Created by Guest User on 4/3/15.
//
//

#ifndef __castlewars__GameScene__
#define __castlewars__GameScene__

#include "cocos2d.h"
#include "Player.h"
#include "AICore.h"
#include "NetworkLogic.h"

using namespace cocos2d;

class   GameScene : cocos2d::CCLayer
{

    
private:
    bool    running;

    int     turn;
    Player  *currentPlayer;
    Player  *currentOpponent;
    bool    newTurn;
    bool    extraTurn;
    
    Player*     p1;
    Player*     p2;
    
    CCLabelTTF* p1Magic;
    CCLabelTTF* p1Gems;
    CCLabelTTF* p1Name;
    CCLabelTTF* p1Castle;
    CCLabelTTF* p1Wall;
    
    CCLabelTTF* p2Magic;
    CCLabelTTF* p2Gems;
    CCLabelTTF* p2Name;
    CCLabelTTF* p2Castle;
    CCLabelTTF* p2Wall;
    
    CCSprite    *bgGame;
    CCSprite    *endGame;
    CCMenu      *cardsMenu;
    std::vector<CCLabelTTF *>   endValues;
    
    CCSize      screenSize;    
    
    AICore      *core;
    
    SRes::playResults   r;
    
    NetworkLogic    *netLog;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    CREATE_FUNC(GameScene);
    
    virtual bool init();
    virtual void update(float);
    static CCScene  *createScene();
    
private:
    void            createGameScene(CCSize);
    
    CCMenuItemImage *createButton(const char *plain, const char *focus, int tag,
                                  int posX, int posY, float scale,
                                  SEL_MenuHandler callBack);
    CCMenuItemImage *createButtonFromCard(Card *, int tag);
    CCMenuItemImage *createDiscardButton(int tag);
    
public:
    
    void popCardMenuItem(int);
    void addCardMenuItem();
    
    void startTurn();
    void endTurn();
    
    void computerTurn();
    void computerPlay(int, CCArray *);
    void computerDiscard(Card*, int);
    
    CCArray    *applyCardEffects(Player *current, Player *opp);
    
    void checkGameOver();
    void gameOver(bool hasWon);
    
    void endButton(CCObject *pSend);
    void cardClick(CCObject *pSend);
    void cardDiscardButton(CCObject *pSend);
    void startExplosion(CCPoint pos);
    
    void    applyPGemEffect();
    void    applyPWallEffect();
    void    applyPCastleEffect();
    void    applyPMagicEffect();
    void    applyOGemEffect();
    void    applyOWallEffect();
    void    applyOCastleEffect();
    void    applyOMagicEffect();
    
    void    removeGameScene();
    
    void    setNetworkLogic(NetworkLogic *);
};

#endif /* defined(__castlewars__GameScene__) */
