//
//  CrystalNode.h
//  castlewars
//
//  Created by admin on 4/28/15.
//
//

#ifndef __castlewars__CrystalNode__
#define __castlewars__CrystalNode__

#include <iostream>
#include "Card.h"
#include "Player.h"

class CrystalNode {
    
private:
    
public:
    CrystalNode() {};
    ~CrystalNode() {}
    
    static bool    getValue(Card *, Player *);
};

#endif /* defined(__castlewars__CrystalNode__) */
