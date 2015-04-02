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
    int crystals;
    int magic;
    int castle;
    int wall;
    std::vector<Card*> Deck;
    std::vector<Card*> Hand;
    std::vector<Card*> Discard;
    
public:
    Player();
    ~Player() {}
    
    const int getCrystals();
    const int getMagic();
    const int getCastle();
    const int getWall();
    
    void setCrystals(const int);
    void setMagic(const int);
    void setCastle(const int);
    void setWall(const int);
    
    void handleNewTurn();
    void shuffle();
};

#endif /* defined(__castlewars__Player__) */
