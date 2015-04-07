//
//  Card.h
//  castlewars
//
//  Created by admin on 3/17/15.
//
//

#ifndef __castlewars__Card__
#define __castlewars__Card__

#include <iostream>
#include "Player.h"
#include "cocos2d.h"

class Player;

typedef bool (*ptrfunc)(Player *, Player *);

class Card {
    
private:
    int cost;
    Player *p1;
    Player *p2;
    ptrfunc effect;
    cocos2d::CCSprite* image;
    
public:
    Card(ptrfunc effect, int value, cocos2d::CCSprite* image);
    ~Card() {}
    
    const int getCost();
    const ptrfunc getEffect();
    
    const cocos2d::CCSprite* getImage();
    //image getter here
    
    static void damage(Player *player, int damage);
    static void damageCastle(Player *player, int damage);
    
    static bool stripMining(Player *player1, Player *player2);
    static bool stoneGiant(Player *player1, Player *player2);
    static bool sheepishRabbit(Player *player1, Player *player2);
    static bool rubyWand(Player *player1, Player *player2);
    static bool rockSlasher(Player *player1, Player *player2);
    static bool recycledRainbows(Player *player1, Player *player2);
    static bool protectionWard(Player *player1, Player *player2);
    static bool mortarMole(Player *player1, Player *player2);
    static bool mobbinGoblin(Player *player1, Player *player2);
    static bool manaStompers(Player *player1, Player *player2);
    static bool manaDisease(Player *player1, Player *player2);
    static bool magicMiners(Player *player1, Player *player2);
    static bool instantWall(Player *player1, Player *player2);
    static bool insecureWall(Player *player1, Player *player2);
    static bool harmonicOrc(Player *player1, Player *player2);
    static bool friendship(Player *player1, Player *player2);
    static bool flyinGoblin(Player *player1, Player *player2);
    static bool emeraldWand(Player *player1, Player *player2);
    static bool clubbinGoblin(Player *player1, Player *player2);
    static bool bowminGoblin(Player *player1, Player *player2);
    static bool bottledFlatulence(Player *player1, Player *player2);
    static bool amethystWand(Player *player1, Player *player2);
    
    static std::vector<Card *> &getNewDeck();
};

#endif /* defined(__castlewars__File__) */