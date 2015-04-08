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

Player::Player()
{
    this->setMagic(1);
    this->setCrystals(3);
    this->setWall(0);
    this->setCastle(15);
    
    this->Hand = *new std::vector<Card *>;
    this->Deck = *new std::vector<Card *>;
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

Card    *Player::getCard(int position) {
    return this->Hand[position];
}

void Player::setCastle(const int value)
{
    this->castle = value;
}

void Player::setWall(const int value)
{
    this->wall = value;
}

void Player::setMagic(const int value)
{
    this->magic = value;
}

void Player::setCrystals(const int value)
{
    this->crystals = value;
}

void Player::handleNewTurn()
{
    this->crystals += this->magic;
    
}

void Player::draw() {
    if (this->Hand.size() >= 5) return;
    if (this->Deck.empty()) shuffle();
    this->Hand.push_back(this->Deck.back());
    this->Deck.pop_back();
}


void Player::shuffle()
{
    printf("deck shuffled and restocked\n");
    while (!this->Discard.empty()) {
        this->Deck.push_back(this->Discard.back());
        this->Discard.pop_back();
    }
    std::random_shuffle(this->Deck.begin(), this->Deck.end());
}




