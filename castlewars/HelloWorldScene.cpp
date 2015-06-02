#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = CCScene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
   
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	

	

	
	// Photonネットワーククラスのインスタンスを作成
    networkLogic = new NetworkLogic();
	//networkLogic = new NetworkLogic(L"1.0");
 
	// 毎フレームでupdateを実行させる
	this->schedule(schedule_selector(HelloWorld::update));
	this->scheduleUpdate();
    
    return true;
}


void HelloWorld::update(float delta)
{
	networkLogic->run();
 
	switch (networkLogic->getState()) {
		case STATE_CONNECTED:
			CCLOG("connected");
		case STATE_LEFT:
			// ルームが存在すればジョイン、なければ作成する
			if (networkLogic->isRoomExists()) {
				CCLOG("Join");
				networkLogic->setLastInput(INPUT_2);
			} else {
				CCLOG("Create");
				networkLogic->setLastInput(INPUT_1);
			}
			break;
		case STATE_DISCONNECTED:
			CCLOG("disconnected");
			// 接続が切れたら再度接続
			networkLogic->connect();
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