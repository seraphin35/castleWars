//
//  File.cpp
//  castlewars
//
//  Created by Guest User on 3/12/15.
//
//

#include "Player.h"
#include "Card.h"
#include <algorithm>
#include "SimpleAudioEngine.h"

Player::Player()
{
    this->magic = 1;
    this->crystals = 3;
    this->wall = 0;
    this->castle = 15;
    
    for (int i = 0; i < 5; i++) this->hand[i] = NULL;
    this->Deck = new std::vector<Card *>;
    this->Discard = Card::getNewDeck();
}

const int Player::getCastle()
{
    return this->castle;
}

const int Player::getCrystals()
{
    return this->crystals;
}

const int Player::getMagic()
{
    return this->magic;
}

const int Player::getWall()
{
    return this->wall;
}

Card    *Player::getCard(int pos) {
    return this->hand[pos];
}

void Player::setCastle(const int value)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(value > this->castle ?
                                                                 "castleUp.wav" : "castleDown.wav");
    this->castle = value;
}

void Player::setWall(const int value)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(value > this->wall ?
                                                                 "wallUp.wav" : "wallDown.wav");
    this->wall = value <= 0 ? 0 : value;
}

void Player::setMagic(const int value)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(value > this->magic ?
                                                                 "magUp.wav" : "magDown.wav");
    this->magic = value;
}

void Player::setCrystals(const int value)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(value > this->crystals ?
                                                                 "gemUp.wav" : "gemDown.wav");
    this->crystals = value;
}

void Player::handleNewTurn()
{
    this->crystals += this->magic;
    
}

int     Player::draw() {
    int pos;
    for (int i = 0; i < 5; i++) {
        if (this->hand[i] == NULL) pos = i;
    }
    if (this->Deck->empty()) shuffle();
    this->hand[pos] = this->Deck->back();
    printf("draw in slot %d - Deck : %lu - Discard : %lu\n",pos, this->Deck->size(), this->Discard->size());
    this->Deck->pop_back();
    return pos;
}

void    Player::discard(int pos) {
    this->Discard->push_back(this->hand[pos]);
    this->hand[pos] = NULL;
}


void Player::shuffle()
{
    
    printf("deck shuffled and restocked\n");
    while (!this->Discard->empty()) {
        this->Deck->push_back(this->Discard->back());
        this->Discard->pop_back();
    }
    for (std::vector<Card *>::iterator it= Deck->begin(); it!=Deck->end(); ++it)
        printf("Before : %s\n", (*it)->getImage());
    std::srand(unsigned (std::time(0)));
    std::random_shuffle(this->Deck->begin(), this->Deck->end());
    for (std::vector<Card *>::iterator it= Deck->begin(); it!=Deck->end(); ++it)
        printf("After : %s\n", (*it)->getImage());
}




