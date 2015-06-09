//
//  NetworkLogicManager.cpp
//  castlewars
//
//  Created by admin on 6/9/15.
//
//

#include "NetworkLogicManager.h"

NetworkLogic    *NetworkLogicManager::getNetLog() {
     static bool done = false;
     if (!done) {
         this->netLog = new NetworkLogic();
         done = true;
     }
     
     return  this->netLog;
}