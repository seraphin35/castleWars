//
//  AICore.cpp
//  castlewars
//
//  Created by admin on 4/28/15.
//
//

#include "AICore.h"
#include "CrystalNode.h"
#include "PlayerWinNode.h"
#include "OppWinNode.h"
#include "CardValueNode.h"
#include "DiscardValueNode.h"

// Constructor allows choosing AI level
AICore::AICore(AI_Mode mode) {
    this->mode = mode;
}

// Manual choosing AI level
void    AICore::setAILevel(AICore::AI_Mode mode) {
    this->mode = mode;
}

// Uses the algorithm's classes to calculate each card's value
void    AICore::setValues(Card **hand, Player *player, Player *opp) {
    for (int i = 0; i < 5; i++) {
        
        // Is the card playable this turn ?
        values[i].playable      = CrystalNode::getValue(hand[i], player);
        
        // Is this card a winning move ?
        values[i].allowWin      = PlayerWinNode::getValue(hand[i], player, opp);
        
        // Is his card a losing move ?
        values[i].opponentWin   = OppWinNode::getValue(hand[i], player, opp);
        
        // What's the overall value of this card ?
        values[i].value         = CardValueNode::getValue(hand[i]);
        
        //Is this card worth discarding ?
        values[i].discardValue  = DiscardValueNode::getValue(hand[i], player);
    }
}

// Choose the best card in the hand
AIReport    AICore::getBestMove(Card **hand, Player *player, Player *opp) {
    this->setValues(hand, player, opp);
    
    switch (this->mode) {
        case EASY:
            return this->getEasyValue(hand, player, opp);
            break;
        case MEDIUM:
            return this->getMediumValue(hand, player, opp);
            break;
        default:
            return this->getHardValue(hand, player, opp);
            break;
    }
}

// Easy algorithm analysis
AIReport    AICore::getEasyValue(Card **, Player *, Player *) {
    AIReport    report;
    int         best = 0;
    
    report.bestMovePosition = -1;
    report.discard = false;
    
    for (int i = 0; i < 5; i++) {
        int value = 0;
        
        value += values[i].value;               //CardValue node check
        value *= (values[i].playable ? 1 : 0);  //Crystal node check
        
        if (value > best) {
            best = value;
            report.bestMovePosition = i;
        }
    }
    
    if (report.bestMovePosition == -1) {
        report.bestMovePosition = 0;
        report.discard = true;
    }
    
    return report;
}

// Medium algorithm analysis
AIReport    AICore::getMediumValue(Card **hand, Player *player, Player *opp) {
    AIReport    report;
    int         best = 0;
    
    report.bestMovePosition = -1;
    report.discard = false;
    
    for (int i = 0; i < 5; i++) {
        int value = 0;
        
        value += values[i].value;                   //CardValue node check
        value += (values[i].allowWin ? 100 : 0);    //PlayerWin node check
        value *= (values[i].opponentWin ? 0 : 1);   //OppWin node check
        value *= (values[i].playable ? 1 : 0);      //Crystal node check
        
        if (value > best) {
            best = value;
            report.bestMovePosition = i;
        }
    }
    
    if (report.bestMovePosition == -1) {
        report.bestMovePosition = 0;
        report.discard = true;
    }
    
    return report;
}

// Hard algorithm analysis
AIReport    AICore::getHardValue(Card **hand, Player *player, Player *opp) {
    AIReport    report;
    int         best = 0;
    
    report.bestMovePosition = -1;
    report.discard = false;
    
    for (int i = 0; i < 5; i++) {
        int value = 0;
        
        value += values[i].value;                   //CardValue node check
        value += (values[i].allowWin ? 100 : 0);    //PlayerWin node check
        value *= (values[i].opponentWin ? 0 : 1);   //OppWin node check
        value *= (values[i].playable ? 1 : 0);      //Crystal node check
        if (values[i].discardValue > value) {       //DiscardValue node check
            value = values[i].discardValue;
            report.discard = true;
        }
        
        if (value > best) {
            best = value;
            report.bestMovePosition = i;
        }
    }
    
    if (report.bestMovePosition == -1) {
        report.bestMovePosition = 0;
        report.discard = true;
    }
    
    return report;
}