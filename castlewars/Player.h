//
//  Player.h
//  castlewars
//
//  Created by Guest User on 3/12/15.
//
//

#ifndef __castlewars__Player__
#define __castlewars__Player__

#include <iostream>
#include <vector>
#include "Card.h"
#include "SRes.h"

class Card;

class Player
{
public:
    enum playerType {
        HUMAN,
        COMPUTER
    };
    
private:
    int gems;
    int magic;
    int castle;
    int wall;
    
    char    *name;
    playerType type;
    
    bool    locked;
    
    Card    *hand[5];
    std::vector<Card*> *Deck;
    std::vector<Card*> *Discard;
    
public:
    Player(char *name, playerType);
    ~Player() {}
    
    void    lock();
    void    unlock();
    bool    isLocked();
    
    const int   getGems();
    const int   getMagic();
    const int   getCastle();
    const int   getWall();
    const char  *getName();
    Card        *getCard(int pos);
    playerType  getType();
    
    void addGems(const int);
    void addMagic(const int);
    void addCastle(const int);
    void addWall(const int);
    
    void    startTurn();
    SRes::playResults    play(int pos);
    void    endTurn();
    
    int     draw();
    void    discard(int pos);

    void    shuffle();
};

#endif /* defined(__castlewars__Player__) */
