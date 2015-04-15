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
#include <unistd.h>

Player::Player()
{
    this->magic = 3;
    this->gems = 10;
    this->wall = 10;
    this->castle = 15;
    
    this->won = false;
    
    for (int i = 0; i < 5; i++) this->hand[i] = NULL;
    this->Deck = new std::vector<Card *>;
    this->Discard = Card::getNewDeck();
}

const int Player::getCastle()
{
    return this->castle;
}

const int Player::getGems()
{
    return this->gems;
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

void Player::addCastle(const int value)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("castleUp.wav");
    this->castle += value;
    if (castle >= 30) this->won = true;
}

void Player::removeCastle(const int value)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("castleDown.wav");
    this->castle -= value;
    if (castle <= 0) {
        this->castle = 0;
        this->won = true;
    }
}

void Player::addWall(const int value)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("wallUp.wav");
    this->wall += value;
}

void Player::removeWall(const int value)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("wallDown.wav");
    this->wall -= value;
    if (this->wall < 0) this->wall = 0;
}

void Player::addMagic(const int value)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("magUp.wav");
    this->magic += value;
}

void Player::removeMagic(const int value)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("magDown.wav");
    this->magic -= value;
    if (this->magic <= 0) this->magic = 1;
}

void Player::addGems(const int value)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("gemUp.wav");
    this->gems += value;
}

void Player::removeGems(const int value)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("gemDown.wav");
    this->gems -= value;
    if (this->gems < 0) this->gems = 0;
}

void Player::handleNewTurn()
{
    this->gems += this->magic;
    
}

int     Player::draw() {
    int pos = 0;
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

int myrandom (int i) { return std::rand()%i;}

void Player::shuffle()
{
    printf("deck shuffled and restocked\n");
    while (!this->Discard->empty()) {
        this->Deck->push_back(this->Discard->back());
        this->Discard->pop_back();
    }
    for (std::vector<Card *>::iterator it= Deck->begin(); it!=Deck->end(); ++it)
        printf("Before : %s\n", (*it)->getImage());
    std::random_shuffle(this->Deck->begin(), this->Deck->end(), myrandom);
    for (std::vector<Card *>::iterator it= Deck->begin(); it!=Deck->end(); ++it)
        printf("After : %s\n", (*it)->getImage());
}




