//
//  PlayerWinNode.cpp
//  castlewars
//
//  Created by admin on 4/28/15.
//
//

#include "PlayerWinNode.h"

bool    PlayerWinNode::getValue(Card *card, Player *player, Player *opp) {
    SRes::playResults res = card->getEffect()();
    
    return (player->getCastle() + res.pCastleMod >= 30 ||
            opp->getCastle() + res.oppCastleMod <= 0);
}