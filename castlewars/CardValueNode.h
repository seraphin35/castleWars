//
//  CardValueNode.h
//  castlewars
//
//  Created by admin on 4/28/15.
//
//

#ifndef __castlewars__CardValueNode__
#define __castlewars__CardValueNode__

#include <iostream>

#include "Card.h"
#include "Player.h"

class CardValueNode {
    
public:
    CardValueNode() {};
    ~CardValueNode() {}
    
    static int getValue(Card *);
};

#endif /* defined(__castlewars__CardValueNode__) */
