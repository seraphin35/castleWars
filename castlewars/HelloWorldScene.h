#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "NetworkLogic.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	
private:
	virtual void update(float delta);
 
 
	NetworkLogic* networkLogic;
};

#endif // __HELLOWORLD_SCENE_H__
