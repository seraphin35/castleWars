//
//  AICore.h
//  castlewars
//
//  Created by admin on 4/28/15.
//
//

#ifndef __castlewars__AICore__
#define __castlewars__AICore__

#include <iostream>
#include "Card.h"

typedef struct s_cardValues
{
    bool    playable;
    bool    allowWin;
    bool    opponentWin;
    int     value;
    int     discardValue;
    
}   cardValues;

typedef struct s_AIReport
{
    short   bestMovePosition;
    bool    discard;
}   AIReport;

class   AICore {
public:
    enum    AI_Mode {
        EASY,
        MEDIUM,
        HARD
    };
    
    cardValues  values[5];
    AI_Mode     mode;
    
public:
    AICore(AI_Mode);
    ~AICore() {}
    
    void        setAILevel(AI_Mode);
    AIReport    getBestMove(Card **, Player *, Player *);
    
private:
    AIReport    getEasyValue(Card **, Player *, Player *);
    AIReport    getMediumValue(Card **, Player *, Player *);
    AIReport    getHardValue(Card **, Player *, Player *);
    
    void        setValues(Card **, Player *,  Player *);
};

#endif /* defined(__castlewars__AICore__) */
