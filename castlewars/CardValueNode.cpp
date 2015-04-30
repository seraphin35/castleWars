//
//  CardValueNode.cpp
//  castlewars
//
//  Created by admin on 4/28/15.
//
//

#include "CardValueNode.h"

int CardValueNode::getValue(Card *card) {
    SRes::playResults res = card->getEffect()();
    
    if (res.extraTurn) return 100;
    
    int value = 0;
    
    value += res.pGemMod;
    value += res.pMagMod * 3;
    value += res.pCastleMod;
    value += res.pWallMod;
    value -= res.oppGemMod;
    value -= res.oppMagMod * 3;
    value -= res.oppCastleMod;
    value -= res.oppWallMod;
    
    return value;
}