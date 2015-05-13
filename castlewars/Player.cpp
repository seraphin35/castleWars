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

Player::Player(char *name, playerType type)
{
    this->magic = 3;
    this->gems = 10;
    this->wall = 10;
    this->castle = 15;
    
    this->name = name;
    this->type = type;
    
    this->locked = false;
    
    for (int i = 0; i < 5; i++) this->hand[i] = NULL;
    this->Deck = new std::vector<Card *>;
    this->Discard = Card::getNewDeck();
}

void    Player::lock() {
    this->locked = true;
    printf("    locking %s\n", this->name);
}

void    Player::unlock() {
    this->locked = false;
    printf("    unlocking %s\n", this->name);
}

bool    Player::isLocked() {
    return this->locked;
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

Player::playerType  Player::getType() {
    return this->type;
}

void Player::addCastle(const int value)
{
    if (value == 0) return;
    printf("        %s gains %d castle\n", this->name, value);
    this->castle += value;
    if (castle <= 0) this->castle = 0;
}

void Player::addWall(const int value)
{
    if (value == 0) return;
    printf("        %s gains %d wall\n", this->name, value);
    this->wall += value;
    if (this->wall < 0) this->wall = 0;
}

void Player::addMagic(const int value)
{
    if (value == 0) return;
    printf("        %s gains %d magic\n", this->name, value);
    this->magic += value;
    if (this->magic < 0) this->magic = 1;
}

void Player::addGems(const int value)
{
    if (value == 0) return;
    printf("        %s gains %d gems\n", this->name, value);
    this->gems += value;
    if (this->gems < 0) this->gems = 0;
}

void Player::startTurn()
{
    this->gems += this->magic;
    this->unlock();
}

SRes::playResults    Player::play(int pos) {
    Card    *card = this->hand[pos];
    SRes::playResults results;

    results.success = false;
    if (card->getCost() <= this->gems) {
        this->addGems(-card->getCost());
        results = card->getEffect()();
    }
    return results;
}

void Player::endTurn() {
    this->lock();
}

int     Player::draw() {
    int pos = 0;
    for (int i = 0; i < 5; i++) {
        if (this->hand[i] == NULL) pos = i;
    }
    if (this->Deck->empty()) shuffle();
    this->hand[pos] = this->Deck->back();
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
    while (!this->Discard->empty()) {
        this->Deck->push_back(this->Discard->back());
        this->Discard->pop_back();
    }
    std::random_shuffle(this->Deck->begin(), this->Deck->end(), myrandom);
}




