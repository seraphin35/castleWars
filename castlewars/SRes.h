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
#include "CCParticleExamples.h"
#include "SimpleAudioEngine.h"

class SRes
{
public:
    static SRes& getInstance()
    {
        static SRes    instance;

        return instance;
    }
    
    enum    SoundID {
        BGM_GAME,
        BGM_MENU,
        CASTLE_DOWN,
        CASTLE_UP,
        GEM_DOWN,
        GEM_UP,
        WALL_DOWN,
        WALL_UP,
        MAGIC_DOWN,
        MAGIC_UP
    };
    
    enum    ResID {
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
        MAGIC_MINERS = 21,
        BANNER_BLUE = 22,
        BANNER_RED = 23,
        RETURN_BTN = 24,
        DEFEAT_BG = 25,
        LEAVE_BTN = 26,
        QUIT_BTN = 27,
        VICTORY_BG = 28,
        GAME_BG = 29,
        MENU_BG = 30,
        STATS_BG = 31,
        MULTI_BTN = 32,
        SOLO_BTN = 33,
        STATS_BTN = 34,
        BTN_BG = 35,
        STAR = 36
    };
    
    enum    PointID {
        CCP_GEM,
        CCP_MAGIC,
        CCP_CASTLE,
        CCP_WALL
    };
    
    typedef struct s_endGameInfos
    {
        int     turn;
        int     p1Castle;
        int     p2Castle;
        int     p1Wall;
        int     p2Wall;
        bool    hasWon;
    }   endGameInfos;
    
    typedef struct s_playResults
    {
        ResID   cardID;
        bool    success;
        bool    extraTurn;
        int pGemMod;
        int pMagMod;
        int pCastleMod;
        int pWallMod;
        int oppGemMod;
        int oppMagMod;
        int oppCastleMod;
        int oppWallMod;
    }   playResults;
    
    typedef playResults (*ptrfunc)();
    
private:
    SRes() {};
    SRes(SRes const&);              // Don't Implement
    void operator=(SRes const&); // Don't implement
    
    void    initiateSprites();
    void    initiateAudio();
    
public:
    void    initRessources();
    
    cocos2d::CCSprite    *getSprite(ResID);
    cocos2d::CCSprite    *getSpriteCopy(ResID);
    
    void    playSound(SoundID);
    void    stopSound();
    
    cocos2d::CCPoint getPoint(PointID, bool);
    
    void           setEndGameInfos(int, int, int, int, int, bool);
    endGameInfos    getEndGameInfos();
    cocos2d::CCParticleExplosion *getExplosion(cocos2d::CCPoint);
    
private:
    cocos2d::CCSprite    *sprites[37];
    CocosDenshion::SimpleAudioEngine    *engine;
    bool    BGMplaying;
    endGameInfos infos;
    cocos2d::CCSize  screenSize;
    
public:
    bool    onlinePlay = false;
    bool    playFirst = false;
    
};

#endif /* defined(__castlewars__File__) */
