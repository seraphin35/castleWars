//
//  File.cpp
//  castlewars
//
//  Created by Guest User on 3/12/15.
//
//

#include "Player.h"
#include "Card.h"

Player::Player()
{
    this->setMagic(1);
    this->setCrystals(3);
    this->setWall(0);
    this->setCastle(15);
    this->shuffle();
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

void Player::newTurn()
{
    this->crystals += this->magic;
    
}

void Player::shuffle()
{
    
}