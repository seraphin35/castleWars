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
#include "SRes.h"

class Player;

class Card {

public:
    
private:
    int         cost;
    SRes::ptrfunc   effect;
    char        *image;
    SRes::ResID id;
    
public:
    Card(SRes::ResID id, SRes::ptrfunc effect, int cost, char *image);
    ~Card() {}
    
    const int getCost();
    const SRes::ptrfunc getEffect();
    
    const char *getImage();
    //image getter here

    const SRes::ResID getID();

    static SRes::playResults getCardReport(bool success, bool extraTurn, SRes::ResID id,
                                     int pGemMod, int pMagMod, int pCastleMod, int pWallMod,
                                     int oppGemMod, int oppMagMod, int oppCastleMod, int oppWallMod);
    
    static void damage(Player *player, int damage);
    static void damageCastle(Player *player, int damage);
    
    static SRes::playResults stripMining();
    static SRes::playResults stoneGiant();
    static SRes::playResults sheepishRabbit();
    static SRes::playResults rubyWand();
    static SRes::playResults rockSlasher();
    static SRes::playResults recycledRainbows();
    static SRes::playResults protectionWard();
    static SRes::playResults mortarMole();
    static SRes::playResults mobbinGoblin();
    static SRes::playResults manaStompers();
    static SRes::playResults manaDisease();
    static SRes::playResults magicMiners();
    static SRes::playResults instantWall();
    static SRes::playResults insecureWall();
    static SRes::playResults harmonicOrc();
    static SRes::playResults friendship();
    static SRes::playResults flyinGoblin();
    static SRes::playResults emeraldWand();
    static SRes::playResults clubbinGoblin();
    static SRes::playResults bowminGoblin();
    static SRes::playResults bottledFlatulence();
    static SRes::playResults amethystWand();
    
    static std::vector<Card *> *getNewDeck();
};

#endif /* defined(__castlewars__File__) */