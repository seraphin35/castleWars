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

class Card;

class Player
{
private:
    int gems;
    int magic;
    int castle;
    int wall;
    
    bool    won;
    
    Card    *hand[5];
    std::vector<Card*> *Deck;
    std::vector<Card*> *Discard;
    
public:
    Player();
    ~Player() {}
    
    const int   getGems();
    const int   getMagic();
    const int   getCastle();
    const int   getWall();
    Card        *getCard(int pos);
    
    void addGems(const int);
    void removeGems(const int);
    void addMagic(const int);
    void removeMagic(const int);
    void addCastle(const int);
    void removeCastle(const int);
    void addWall(const int);
    void removeWall(const int);
    
    void handleNewTurn();
    
    int     draw();
    void    discard(int pos);

    void    shuffle();
};

#endif /* defined(__castlewars__Player__) */
