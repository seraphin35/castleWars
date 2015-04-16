//
//  StatScene.cpp
//  castlewars
//
//  Created by Guest User on 4/16/15.
//
//

#include "StatScene.h"
#include "MainMenuScene.h"
#include "SRes.h"

CCScene*    Stat::createScene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    CCLayer *layer = Stat::create();
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool    Stat::init()
{
    // get screen size
	this->screenSize = CCDirector::sharedDirector()->getWinSize();

    this->createStatScene(screenSize);
    
    return true;
}

void    Stat::createStatScene(CCSize screenSize)
{
    this->bgStat = CCSprite::create("statsBG.png");
    this->bgStat->setPosition(ccp(this->screenSize.width / 2, this->screenSize.height / 2));
    
    this->returnBtn = CCMenuItemImage::create("returnBtn.png",
                                              "returnBtn.png",
                                              this,
                                              menu_selector(Stat::returnMenu));

    this->returnBtn->setPosition(ccp(this->screenSize.width / 2,
                                     this->screenSize.height - this->returnBtn->getContentSize().height));
    
    this->addChild(bgStat, 1);
    
    // add buttons
    CCMenu  *menu = CCMenu::create(returnBtn, NULL);
    menu->setPosition( CCPointZero );
    this->addChild(menu, 2);
    
    // read value file and print it
    // if doesn't exist, create an empty one
}

void    Stat::returnMenu()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.8, MainMenu::scene()));
}