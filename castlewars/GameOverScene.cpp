//
//  GameOverScene.cpp
//  castlewars
//
//  Created by Guest User on 4/16/15.
//
//

#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "SRes.h"
#include "cocos2d.h"

CCScene*    GameOver::createScene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    CCLayer *layer = GameOver::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool    GameOver::init()
{
    // get screen size
	this->screenSize = CCDirector::sharedDirector()->getWinSize();
    
    this->createStatScene(screenSize);
    
    return true;
}

void    GameOver::createStatScene(CCSize screenSize)
{
    SRes::endGameInfos infos = SRes::getInstance().getEndGameInfos();
    
    if (infos.hasWon)
        this->bgGameOver = CCSprite::create("victoryBG.png");
    else
        this->bgGameOver = CCSprite::create("defeatBG.png");
    
    this->bgGameOver->setScaleX(screenSize.width / this->bgGameOver->getContentSize().width);
    this->bgGameOver->setScaleY(screenSize.height / this->bgGameOver->getContentSize().height);
    this->bgGameOver->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->bgGameOver->setPosition(ccp(screenSize.width / 2, screenSize.height / 2));
    this->addChild(this->bgGameOver, 2);
    
    // display bgGameOver informations
    CCString    nbTurnStr           =   *CCString::createWithFormat("%d", infos.turn);
    CCString    nbP1CastlePointStr  =   *CCString::createWithFormat("%d", infos.p1Castle);
    CCString    nbP2CastlePointStr  =   *CCString::createWithFormat("%d", infos.p2Castle);
    CCString    nbP1WallsPointStr   =   *CCString::createWithFormat("%d", infos.p1Wall);
    CCString    nbP2WallsPointStr   =   *CCString::createWithFormat("%d", infos.p2Wall);
    
    CCLabelTTF  *nbTurn             =   CCLabelTTF::create(nbTurnStr.getCString(), "MagicFont", 20,
                                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCLabelTTF  *nbP1CastlePoint    =   CCLabelTTF::create(nbP1CastlePointStr.getCString(), "MagicFont", 20,
                                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCLabelTTF  *nbP1WallsPoint     =   CCLabelTTF::create(nbP1WallsPointStr.getCString(), "MagicFont", 20,
                                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCLabelTTF  *nbP2CastlePoint    =   CCLabelTTF::create(nbP2CastlePointStr.getCString(), "MagicFont", 20,
                                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    CCLabelTTF  *nbP2WallsPoint     =   CCLabelTTF::create(nbP2WallsPointStr.getCString(), "MagicFont", 20,
                                                           CCSizeMake(245, 32), kCCTextAlignmentCenter);
    
    nbTurn->setPosition(ccp(screenSize.width / 2 + 105, screenSize.height / 2 + 80));
    nbP1CastlePoint->setPosition(ccp(screenSize.width / 2 + 105, screenSize.height / 2 + 50));
    nbP1WallsPoint->setPosition(ccp(screenSize.width / 2 + 105, screenSize.height / 2 + 20));
    nbP2CastlePoint->setPosition(ccp(screenSize.width / 2 + 105, screenSize.height / 2 - 10));
    nbP2WallsPoint->setPosition(ccp(screenSize.width / 2 + 105, screenSize.height / 2 - 40));
    
    nbTurn->setColor(ccc3(0, 0, 0));
    nbP1CastlePoint->setColor(ccc3(0, 0, 0));
    nbP1WallsPoint->setColor(ccc3(0, 0, 0));
    nbP2CastlePoint->setColor(ccc3(0, 0, 0));
    nbP2WallsPoint->setColor(ccc3(0, 0, 0));
    
    this->endValues.push_back(nbTurn);
    this->endValues.push_back(nbP1CastlePoint);
    this->endValues.push_back(nbP1WallsPoint);
    this->endValues.push_back(nbP2CastlePoint);
    this->endValues.push_back(nbP2WallsPoint);
    
    this->addChild(nbTurn, 2);
    this->addChild(nbP1CastlePoint, 2);
    this->addChild(nbP1WallsPoint, 2);
    this->addChild(nbP2CastlePoint, 2);
    this->addChild(nbP2WallsPoint, 2);
    
    // Create Button to come back to menu
    CCPoint     buttonPos = CCPoint(screenSize.width / 2, screenSize.height / 4 + 10);
    
    CCMenuItemImage *returnToMenu = createButton("btnBG.png",
                                                 "btnBG.png", 1,
                                                 0,
                                                 0 - this->screenSize.height / 4, 1,
                                                 menu_selector(GameOver::endButton));
    CCLabelTTF  *returnToMenuTxt = CCLabelTTF::create("Done", "MagicFont", 24,
                                                      CCSizeMake(245, 32), kCCTextAlignmentCenter);
    returnToMenuTxt->setPosition(buttonPos);
    
    CCMenu  *menu   = CCMenu::create(returnToMenu, NULL);
    this->addChild(menu, 3);
    this->addChild(returnToMenuTxt, 3);
}

CCMenuItemImage *GameOver::createButton(const char *plain, const char *focus, int tag,
                                    int posX, int posY, float scale,
                                    SEL_MenuHandler callBack) {
    CCMenuItemImage *btn = CCMenuItemImage::create(plain, focus, this, callBack);
    btn->setScale(scale);
    btn->setTag(tag);
    btn->setPosition(ccp(posX, posY));
    
    return btn;
}

void    GameOver::endButton(CCObject *pSend)
{
    SRes::getInstance().stopSound();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeDown::create(0.8, MainMenu::scene()));
}