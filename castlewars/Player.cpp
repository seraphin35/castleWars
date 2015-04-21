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
#include "SRes.h"
#include <unistd.h>

Player::Player(char *name)
{
    this->magic = 3;
    this->gems = 10;
    this->wall = 10;
    this->castle = 15;
    
    this->name = name;
    
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

const char *Player::getName() {
    return this->name;
}

Card    *Player::getCard(int pos) {
    return this->hand[pos];
}

void Player::addCastle(const int value)
{
    SRes::getInstance().playSound(SRes::CASTLE_UP);
    this->castle += value;
}

void Player::removeCastle(const int value)
{
    SRes::getInstance().playSound(SRes::CASTLE_DOWN);
    this->castle -= value;
    if (castle <= 0) this->castle = 0;
}

void Player::addWall(const int value)
{
    SRes::getInstance().playSound(SRes::WALL_UP);
    this->wall += value;
}

void Player::removeWall(const int value)
{
    SRes::getInstance().playSound(SRes::WALL_DOWN);
    this->wall -= value;
    if (this->wall < 0) this->wall = 0;
}

void Player::addMagic(const int value)
{
    SRes::getInstance().playSound(SRes::MAGIC_UP);
    this->magic += value;
}

void Player::removeMagic(const int value)
{
    SRes::getInstance().playSound(SRes::MAGIC_DOWN);
    this->magic -= value;
    if (this->magic < 0) this->magic = 1;
}

void Player::addGems(const int value)
{
    SRes::getInstance().playSound(SRes::GEM_UP);
    this->gems += value;
}

void Player::removeGems(const int value)
{
    SRes::getInstance().playSound(SRes::GEM_DOWN);
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
    printf("Discard in slot %d\n", pos);
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
    std::random_shuffle(this->Deck->begin(), this->Deck->end(), myrandom);
}




