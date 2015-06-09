//
//  NetworkLogicManager.cpp
//  castlewars
//
//  Created by admin on 6/9/15.
//
//

#include "NetworkLogicManager.h"

NetworkLogic    *NetworkLogicManager::getNetLog() {
    if (!this->init) {
        this->netLog = new NetworkLogic();
        this->init = true;
    }
    
    return  this->netLog;
}