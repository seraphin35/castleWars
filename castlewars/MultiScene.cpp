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
    
    this->netLog = new NetworkLogic();
    
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
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.8, MainMenu::scene()));
}

void MultiScene::update()
{
	netLog->run();
    
	switch (netLog->getState()) {
		case STATE_CONNECTED:
			CCLOG("connected");
		case STATE_LEFT:
			// ルームが存在すればジョイン、なければ作成する
			if (netLog->isRoomExists()) {
				CCLOG("Join");
				netLog->setLastInput(INPUT_2);
			} else {
				CCLOG("Create");
				netLog->setLastInput(INPUT_1);
			}
			break;
		case STATE_DISCONNECTED:
			CCLOG("disconnected");
			// 接続が切れたら再度接続
			netLog->connect();
			break;
		case STATE_CONNECTING:
		case STATE_JOINING:
		case STATE_JOINED:
		case STATE_LEAVING:
		case STATE_DISCONNECTING:
			//CCLOG("bbbbb");
		default:
			//CCLOG("default");
			break;
	}
}

void    MultiScene::lookForGame() {
    bool result = false;
    
    result = this->netLog->connect();
    printf("Connected : %d\n", result);
    
    printf("Looking for game ...\n");
    if (this->isRoomAvailable()) {
        printf("Found room(s) !\n");
        if (!this->joinRoom()) {
            printf("Failed to join room, creating one\n");
            result = this->createRoom();
        }
    } else {
        printf("No room, creating one\n");
        result = this->createRoom();
    }
    
    printf("Room created : %d\n", result);
}

bool    MultiScene::isRoomAvailable() {
    return this->netLog->isRoomExists();
}

bool    MultiScene::joinRoom() {
    return this->netLog->opJoinRandomRoom();
}

bool    MultiScene::createRoom() {
    return this->netLog->opCreateRoom();
}

void    MultiScene::leaveRoom() {
    this->netLog->disconnect();
}