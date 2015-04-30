//
//  PlayerWinNode.h
//  castlewars
//
//  Created by admin on 4/28/15.
//
//

#ifndef __castlewars__PlayerWinNode__
#define __castlewars__PlayerWinNode__

#include <iostream>
#include "Card.h"
#include "Player.h"

class PlayerWinNode {
    
private:
    
public:
    PlayerWinNode() {};
    ~PlayerWinNode() {}
    
    static bool    getValue(Card *, Player *, Player *);
};

#endif /* defined(__castlewars__PlayerWinNode__) */
