//
//  File.h
//  castlewars
//
//  Created by admin on 4/9/15.
//
//

#ifndef __castlewars__File__
#define __castlewars__File__

#include <iostream>
#include "CCSprite.h"

class SRes
{
public:
    static SRes& getInstance()
    {
        static SRes    instance;

        return instance;
    }
    
    enum    CardID {
        AMETHYST_WAND = 0,
        BOTTLED_FLATULENCE = 1,
        BOWMIN_GOBLIN = 2,
        CLUBIN_GOBLIN = 3,
        EMERALD_WAND = 4,
        FLYIN_GOBLIN = 5,
        FRIENDSHIP = 6,
        HARMONIC_ORC = 7,
        INSECURE_WALL = 8,
        INSTANT_WALL = 9,
        MANA_DISEASE = 10,
        MANA_STOMPERS = 11,
        MOBBIN_GOBLIN = 12,
        MORTAR_MOLE = 13,
        PROTECTION_WARD = 14,
        RECYCLED_RAINBOW = 15,
        ROCK_SLASHER = 16,
        RUBY_WAND = 17,
        SHEEPISH_RABBIT = 18,
        STONE_GIANT = 19,
        STRIP_MINING = 20,
        MAGIC_MINERS = 21
    };
    
private:
    SRes() {};
    SRes(SRes const&);              // Don't Implement
    void operator=(SRes const&); // Don't implement
    
    void    initiateSprites();
    void    initiateAudio();
    
public:
    void    initRessources();
    
    cocos2d::CCSprite    *getSprite(CardID);
    cocos2d::CCSprite    *getSpriteCopy(CardID);

private:
    cocos2d::CCSprite    *sprites[22];
};

#endif /* defined(__castlewars__File__) */
