//
//  NetworkLogicManager.h
//  castlewars
//
//  Created by admin on 6/9/15.
//
//

#ifndef __castlewars__NetworkLogicManager__
#define __castlewars__NetworkLogicManager__

#include <iostream>

#include "NetworkLogic.h"

class NetworkLogicManager
{
public:
    static NetworkLogicManager& getInstance()
    {
        static NetworkLogicManager    instance;
        
        return instance;
    }
    
private:
    NetworkLogicManager() {};
    NetworkLogicManager(NetworkLogicManager const&);              // Don't Implement
    void operator=(NetworkLogicManager const&); // Don't implement
    
private:
    NetworkLogic    *netLog;
    
public:
    NetworkLogic    *getNetLog();
    

};

#endif /* defined(__castlewars__NetworkLogicManager__) */
