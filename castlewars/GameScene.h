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

using namespace cocos2d;

class   Game : cocos2d::CCLayer
{
private:
    int     turn;
    bool    currentPlayerTurn;

private:
    bool         gameEnd;
    bool    locked;
    
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
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    CREATE_FUNC(Game);
    
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
    
    void startNewTurn(Player *p);
    void switchTurn(bool extra);
    void gameOver(bool hasWon);
    void switchToMainMenu();
    void computerDiscard(Card*, int);
    void computerPlay(Card*, int);
    void computerTurn();
    void cleanSprite(CCSprite *);
    
    void    lockScreen();
    void    unlockScreen();
    bool    isLocked();

    void endButton(CCObject *pSend);
    void cardClick(CCObject *pSend);
    void cardDiscardButton(CCObject *pSend);
    void removeGameScene();
};

#endif /* defined(__castlewars__GameScene__) */
