//
//  DiscardValueNode.cpp
//  castlewars
//
//  Created by admin on 4/28/15.
//
//

#include "DiscardValueNode.h"

int DiscardValueNode::getValue(Card *card, Player *player) {

    return card->getCost() - player->getMagic() * 2;
}
