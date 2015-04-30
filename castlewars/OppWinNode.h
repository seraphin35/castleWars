//
//  OppWinNode.h
//  castlewars
//
//  Created by admin on 4/28/15.
//
//

#ifndef __castlewars__OppWinNode__
#define __castlewars__OppWinNode__

#include <iostream>

#include "Card.h"
#include "Player.h"

class OppWinNode {
    
public:
    OppWinNode() {};
    ~OppWinNode() {}
    
    static bool    getValue(Card *, Player *, Player *);
};

#endif /* defined(__castlewars__OppWinNode__) */
