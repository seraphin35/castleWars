//
//  File.cpp
//  castlewars
//
//  Created by admin on 4/9/15.
//
//

#include "SRes.h"

void    SRes::initRessources() {
    static bool done = false;
    if (done) return;
    this->engine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    this->initiateAudio();
    this->initiateSprites();
    done = true;
}

void    SRes::initiateAudio() {
    this->BGMplaying = false;
    this->engine->preloadBackgroundMusic("gameBGM.mp3");
    this->engine->preloadBackgroundMusic("MainMenu.mp3");
    this->engine->preloadEffect("castleDown.wav");
    this->engine->preloadEffect("castleUp.wav");
    this->engine->preloadEffect("gemDown.wav");
    this->engine->preloadEffect("gemUp.wav");
    this->engine->preloadEffect("wallDown.wav");
    this->engine->preloadEffect("wallUp.wav");
    this->engine->preloadEffect("magicDown.wav");
    this->engine->preloadEffect("magicUp.wav");
    
}

void    SRes::initiateSprites() {
    this->sprites[AMETHYST_WAND] = cocos2d::CCSprite::create("amethyst_wand.png");
    this->sprites[BOTTLED_FLATULENCE] = cocos2d::CCSprite::create("bottled_flatulence.png");
    this->sprites[BOWMIN_GOBLIN] = cocos2d::CCSprite::create("bowmin_goblin.png");
    this->sprites[CLUBIN_GOBLIN] = cocos2d::CCSprite::create("clubin_goblin.png");
    this->sprites[EMERALD_WAND] = cocos2d::CCSprite::create("emerald_wand.png");
    this->sprites[FLYIN_GOBLIN] = cocos2d::CCSprite::create("flyin_goblin.png");
    this->sprites[FRIENDSHIP] = cocos2d::CCSprite::create("friendship.png");
    this->sprites[HARMONIC_ORC] = cocos2d::CCSprite::create("harmonic_orc.png");
    this->sprites[INSECURE_WALL] = cocos2d::CCSprite::create("insecure_wall.png");
    this->sprites[INSTANT_WALL] = cocos2d::CCSprite::create("instant_wall.png");
    this->sprites[MANA_DISEASE] = cocos2d::CCSprite::create("magic_miners.png");
    this->sprites[MANA_STOMPERS] = cocos2d::CCSprite::create("mana_disease.png");
    this->sprites[MOBBIN_GOBLIN] = cocos2d::CCSprite::create("mana_stompers.png");
    this->sprites[MORTAR_MOLE] = cocos2d::CCSprite::create("mobbin_goblin.png");
    this->sprites[PROTECTION_WARD] = cocos2d::CCSprite::create("mortar_mole.png");
    this->sprites[RECYCLED_RAINBOW] = cocos2d::CCSprite::create("protection_ward.png");
    this->sprites[ROCK_SLASHER] = cocos2d::CCSprite::create("recycled_rainbow.png");
    this->sprites[RUBY_WAND] = cocos2d::CCSprite::create("rock_slasher.png");
    this->sprites[SHEEPISH_RABBIT] = cocos2d::CCSprite::create("ruby_wand.png");
    this->sprites[STONE_GIANT] = cocos2d::CCSprite::create("sheepish_rabbit.png");
    this->sprites[STRIP_MINING] = cocos2d::CCSprite::create("stone_giant.png");
    this->sprites[MAGIC_MINERS] = cocos2d::CCSprite::create("strip_mining.png");
    this->sprites[BANNER_BLUE] = cocos2d::CCSprite::create("bannerBlue.png");
    this->sprites[BANNER_RED] = cocos2d::CCSprite::create("bannerRed.png");
    this->sprites[RETURN_BTN] = cocos2d::CCSprite::create("returnBtn.png");
    this->sprites[DEFEAT_BG] = cocos2d::CCSprite::create("defeatBG.png");
    this->sprites[LEAVE_BTN] = cocos2d::CCSprite::create("leaveBtn.png");
    this->sprites[QUIT_BTN] = cocos2d::CCSprite::create("quitBtn.png");
    this->sprites[VICTORY_BG] = cocos2d::CCSprite::create("victoryBG.png");
    this->sprites[GAME_BG] = cocos2d::CCSprite::create("gameBG.png");
    this->sprites[MENU_BG] = cocos2d::CCSprite::create("menuBG.png");
    this->sprites[STATS_BG] = cocos2d::CCSprite::create("statsBG.png");
    this->sprites[MULTI_BTN] = cocos2d::CCSprite::create("multiBtn.png");
    this->sprites[SOLO_BTN] = cocos2d::CCSprite::create("soloBtn.png");
    this->sprites[STATS_BTN] = cocos2d::CCSprite::create("statsBtn.png");
    this->sprites[BTN_BG] = cocos2d::CCSprite::create("btnBG.png");
}

void    SRes::playSound(SRes::SoundID id) {
    switch (id) {
        case BGM_GAME:
            if (this->BGMplaying) this->engine->stopBackgroundMusic(false);
            this->engine->playBackgroundMusic("gameBGM.mp3", true);
            this->BGMplaying = true;
            break;
        case BGM_MENU:
            if (this->BGMplaying) this->engine->stopBackgroundMusic(false);
            this->engine->playBackgroundMusic("MainMenu.mp3", true);
            this->BGMplaying = true;
            break;
        case CASTLE_DOWN:
            this->engine->playEffect("castleDown.wav");
            break;
        case CASTLE_UP:
            this->engine->playEffect("castleUp.wav");
            break;
        case GEM_DOWN:
            this->engine->playEffect("gemDown.wav");
            break;
        case GEM_UP:
            this->engine->playEffect("gemUp.wav");
            break;
        case WALL_DOWN:
            this->engine->playEffect("wallDown.wav");
            break;
        case WALL_UP:
            this->engine->playEffect("wallUp.wav");
            break;
        case MAGIC_DOWN:
            this->engine->playEffect("magicDown.wav");
            break;
        case MAGIC_UP:
            this->engine->playEffect("magicUp.wav");
            break;
    }
    
}

void    SRes::stopSound() {
    this->engine->stopBackgroundMusic(false);
    this->BGMplaying = false;
}

cocos2d::CCSprite   *SRes::getSprite(SRes::ResID id) {
    return this->sprites[id];
}

cocos2d::CCSprite   *SRes::getSpriteCopy(SRes::ResID id) {
    return (cocos2d::CCSprite *) this->sprites[id]->copy();
}