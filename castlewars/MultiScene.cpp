//
//  MultiScene.cpp
//  castlewars
//
//  Created by Guest User on 4/16/15.
//
//

#include "MultiScene.h"
#include "MainMenuScene.h"
#include "SRes.h"
#include "GameScene.h"

CCScene*    MultiScene::createScene()
{
    CCScene *scene = CCScene::create();
    CCLayer *layer = MultiScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool    MultiScene::init()
{
    // get screen size
	this->screenSize = CCDirector::sharedDirector()->getWinSize();
    
    this->createMultiScene(screenSize);
    
    this->netLog = NetworkLogicManager::getInstance().getNetLog();
    this->connected = false;
    this->netRunning = false;
    this->gameStarted = false;
    this->joinAttempt = 0;
    
    this->schedule(schedule_selector(MultiScene::update));
    
    return true;
}

void    MultiScene::createMultiScene(CCSize screenSize)
{
    this->bgMulti = CCSprite::create("statsBG.png");
    this->bgMulti->setPosition(ccp(this->screenSize.width / 2, this->screenSize.height / 2));
    
    this->returnBtn = CCMenuItemImage::create("returnBtn.png",
                                              "returnBtn.png",
                                              this,
                                              menu_selector(MultiScene::returnMenu));
    this->playBtn = CCMenuItemImage::create("returnBtn.png",
                                              "returnBtn.png",
                                              this,
                                              menu_selector(MultiScene::lookForGame));
    
    this->returnBtn->setPosition(ccp(this->screenSize.width / 2,
                                     this->screenSize.height - this->returnBtn->getContentSize().height));
    this->playBtn->setPosition(ccp(this->screenSize.width / 2,
                                     this->screenSize.height / 2));
    
    this->addChild(bgMulti, 1);
    
    // add buttons
    CCMenu  *menu = CCMenu::create(returnBtn, playBtn, NULL);
    menu->setPosition( CCPointZero );
    this->addChild(menu, 2);
    
    // read value file and print it
    // if doesn't exist, create an empty one
}

void    MultiScene::returnMenu()
{
    this->leaveRoom();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.8, MainMenu::scene()));
}

void MultiScene::update()
{
    if (!this->netRunning) {
        this->leaveRoom();
        return;
    }
    
	netLog->run();
    
	switch (netLog->getState()) {
		case STATE_CONNECTED:
		case STATE_LEFT:
			CCLOG("joining new room ...");
			this->createOrJoinRoom();
			break;
		case STATE_DISCONNECTED:
			CCLOG("disconnected. reconnecting ...");
            this->connected = false;
			netLog->connect();
			break;
		case STATE_JOINED:
            this->connected = true;
            break;
		case STATE_CONNECTING:
		case STATE_JOINING:
		case STATE_LEAVING:
		case STATE_DISCONNECTING:
		default:
			//CCLOG("default");
			break;
	}
    
    if (this->connected) {
        switch(this->netLog->lastEvent) {
            case EVENT_OPP_JOINED:
                this->netLog->sendEvent(2, NULL);
                break;
            case EVENT_START_FIRST:
                this->netLog->sendEvent(3, NULL);
                SRes::getInstance().onlinePlay = true;
                this->startGame(true);
                break;
            case EVENT_START_SECOND:
                SRes::getInstance().onlinePlay = true;
                this->startGame(false);
                break;
            default:
                break;
        }
    }
}

void    MultiScene::lookForGame() {
    
    this->netRunning = !this->netRunning;
    return;
}

void    MultiScene::createOrJoinRoom() {
    if (netLog->isRoomExists() && this->joinAttempt < 10) {
        printf("Join attempt n.%d\n", this->joinAttempt + 1);
        netLog->setLastInput(INPUT_2);
        this->joinAttempt++;
    } else {
        this->joinAttempt = 0;
        CCLOG("Create");
        netLog->setLastInput(INPUT_1);
    }
}

void    MultiScene::leaveRoom() {
    this->connected = false;
    this->netLog->disconnect();
}

void    MultiScene::startGame(bool first) {
    if (this->gameStarted) return;

    this->gameStarted = true;
    SRes::getInstance().onlinePlay = true;
    SRes::getInstance().playFirst = first;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCScene *gameScene = GameScene::createScene();
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.8, gameScene));
}