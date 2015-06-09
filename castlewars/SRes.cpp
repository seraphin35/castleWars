//
//  File.cpp
//  castlewars
//
//  Created by admin on 4/9/15.
//
//

#include "SRes.h"
#include "cocos2d.h"

void    SRes::initRessources() {
    static bool done = false;
    if (done) return;
    this->engine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    this->initiateAudio();
    this->initiateSprites();
    this->initiateSpritesPath();
    this->screenSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
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
    this->engine->preloadEffect("magDown.wav");
    this->engine->preloadEffect("magUp.wav");
    
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
    this->sprites[STAR] = cocos2d::CCSprite::create("star.png");
}

void    SRes::initiateSpritesPath() {
    this->path[AMETHYST_WAND] = "amethyst_wand.png";
    this->path[BOTTLED_FLATULENCE] = "bottled_flatulence.png";
    this->path[BOWMIN_GOBLIN] = "bowmin_goblin.png";
    this->path[CLUBIN_GOBLIN] = "clubin_goblin.png";
    this->path[EMERALD_WAND] = "emerald_wand.png";
    this->path[FLYIN_GOBLIN] = "flyin_goblin.png";
    this->path[FRIENDSHIP] = "friendship.png";
    this->path[HARMONIC_ORC] = "harmonic_orc.png";
    this->path[INSECURE_WALL] = "insecure_wall.png";
    this->path[INSTANT_WALL] = "instant_wall.png";
    this->path[MANA_DISEASE] = "magic_miners.png";
    this->path[MANA_STOMPERS] = "mana_disease.png";
    this->path[MOBBIN_GOBLIN] = "mana_stompers.png";
    this->path[MORTAR_MOLE] = "mobbin_goblin.png";
    this->path[PROTECTION_WARD] = "mortar_mole.png";
    this->path[RECYCLED_RAINBOW] = "protection_ward.png";
    this->path[ROCK_SLASHER] = "recycled_rainbow.png";
    this->path[RUBY_WAND] = "rock_slasher.png";
    this->path[SHEEPISH_RABBIT] = "ruby_wand.png";
    this->path[STONE_GIANT] = "sheepish_rabbit.png";
    this->path[STRIP_MINING] = "stone_giant.png";
    this->path[MAGIC_MINERS] = "strip_mining.png";
    this->path[BANNER_BLUE] = "bannerBlue.png";
    this->path[BANNER_RED] = "bannerRed.png";
    this->path[RETURN_BTN] = "returnBtn.png";
    this->path[DEFEAT_BG] = "defeatBG.png";
    this->path[LEAVE_BTN] = "leaveBtn.png";
    this->path[QUIT_BTN] = "quitBtn.png";
    this->path[VICTORY_BG] = "victoryBG.png";
    this->path[GAME_BG] = "gameBG.png";
    this->path[MENU_BG] = "menuBG.png";
    this->path[STATS_BG] = "statsBG.png";
    this->path[MULTI_BTN] = "multiBtn.png";
    this->path[SOLO_BTN] = "soloBtn.png";
    this->path[STATS_BTN] = "statsBtn.png";
    this->path[BTN_BG] = "btnBG.png";
    this->path[STAR] = "star.png";
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
            this->engine->playEffect("magDown.wav");
            break;
        case MAGIC_UP:
            this->engine->playEffect("magUp.wav");
            break;
    }
    
}
void    SRes::setEndGameInfos(int turn, int p1Castle, int p2Castle, int p1Wall, int p2Wall, bool hasWon)
{
    this->infos.turn = turn;
    this->infos.p1Castle = p1Castle;
    this->infos.p2Castle = p2Castle;
    this->infos.p1Wall = p1Wall;
    this->infos.p2Wall = p2Wall;
    this->infos.hasWon = hasWon;
}


SRes::endGameInfos   SRes::getEndGameInfos()
{
    return this->infos;
}

void    SRes::stopSound() {
    this->engine->stopBackgroundMusic(false);
    this->BGMplaying = false;
}

cocos2d::CCPoint    SRes::getPoint(SRes::PointID id, bool player) {
    switch (id) {
        case CCP_GEM:
            return player ?
            ccp(50, screenSize.height - 80) :
            ccp(screenSize.width - 50, screenSize.height - 80);
            break;
        case CCP_MAGIC:
            return player ?
            ccp(100, screenSize.height - 50) :
            ccp(screenSize.width - 100, screenSize.height - 50);
            break;
        case CCP_CASTLE:
            return player ?
            ccp(screenSize.width / 2 - 135, screenSize.height / 2 + 6) :
            ccp(screenSize.width / 2 + 135, screenSize.height / 2 + 6);
            break;
        case CCP_WALL:
            return player ?
            ccp(screenSize.width / 2 - 50, screenSize.height / 2 + 6) :
            ccp(screenSize.width / 2 + 50, screenSize.height / 2 + 6);
            break;
    }
}

cocos2d::CCSprite   *SRes::getSprite(SRes::ResID id) {
    return this->sprites[id];
}

cocos2d::CCSprite   *SRes::getSpriteCopy(SRes::ResID id) {
    return (cocos2d::CCSprite *) this->sprites[id]->copy();
}

char    *SRes::getSpritePath(SRes::ResID id) {
    return this->path[id];
}

cocos2d::CCParticleExplosion    *SRes::getExplosion(cocos2d::CCPoint pos) {
  //  cocos2d::CCSprite *s = getSprite(STAR);
    cocos2d::CCSprite *ss = cocos2d::CCSprite::create("star.png");
    
    cocos2d::CCTexture2D*            texture = ss->getTexture();
    
    cocos2d::CCParticleExplosion*    explosion = new cocos2d::CCParticleExplosion();
    
    explosion->initWithTotalParticles(30);
    explosion->setTexture(texture);
    explosion->setPosition(pos);
    explosion->setDuration(0.01f);
    explosion->setSpeed(200);
    explosion->setGravity(ccp(0, -250));
    explosion->setAngle(90);
    explosion->setAngleVar(10);
    explosion->setStartSize(20);
    explosion->setEndSize(0);
    explosion->setLife(1.0f);
    explosion->setLifeVar(1.0f);
    explosion->setEmissionRate(200);
    explosion->setAutoRemoveOnFinish(true);
    
    return explosion;
}