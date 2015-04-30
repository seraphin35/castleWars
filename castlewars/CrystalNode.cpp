//
//  CrystalNode.cpp
//  castlewars
//
//  Created by admin on 4/28/15.
//
//

#include "CrystalNode.h"

bool    CrystalNode::getValue(Card *card, Player *player) {
    return (player->getGems() >= card->getCost());
}