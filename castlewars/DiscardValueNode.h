//
//  DiscardValueNode.h
//  castlewars
//
//  Created by admin on 4/28/15.
//
//

#ifndef __castlewars__DisDiscardValueNode__
#define __castlewars__DisDiscardValueNode__

#include <iostream>


#include "Card.h"
#include "Player.h"

class DiscardValueNode {
public:
    DiscardValueNode() {};
    ~DiscardValueNode() {}

    static int getValue(Card *, Player *);
};

#endif /* defined(__castlewars__DisDiscardValueNode__) */
