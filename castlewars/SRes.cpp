//
//  File.cpp
//  castlewars
//
//  Created by admin on 4/9/15.
//
//

#include "SRes.h"
#include "SimpleAudioEngine.h"

void    SRes::initRessources() {
    static bool done = false;
    if (done) return;
    this->initiateAudio();
    this->initiateSprites();
    done = true;
}

void    SRes::initiateAudio() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("gameBGM.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("MainMenu.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("castleDown.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("castleUp.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("gemDown.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("gemUp.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("wallDown.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("wallUp.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("magicDown.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("magicUp.wav");
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
}

cocos2d::CCSprite   *SRes::getSprite(SRes::CardID id) {
    return this->sprites[id];
}

cocos2d::CCSprite   *SRes::getSpriteCopy(SRes::CardID id) {
    return (cocos2d::CCSprite *) this->sprites[id]->copy();
}