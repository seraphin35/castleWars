//
//  OppWinNode.cpp
//  castlewars
//
//  Created by admin on 4/28/15.
//
//

#include "OppWinNode.h"

bool    OppWinNode::getValue(Card *card, Player *player, Player *opp) {
    SRes::playResults res = card->getEffect()();
    
    return (player->getCastle() + res.pCastleMod <= 0 ||
            opp->getCastle() + res.oppCastleMod >= 30);
}