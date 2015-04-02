//
//  StripMining.cpp
//  castlewars
//
//  Created by Guest User on 3/31/15.
//
//

#include "Cards.h"

bool stripMining(Player *player1, Player *player2)
{
    int magic = player1->getMagic();
    
    magic -= 1;
    if (magic < 0)
        magic = 0;
    player1->setMagic(magic);
    player1->setWall(player1->getWall() + 10);
    player1->setCrystals(player1->getCrystals() + 5);
    
    return 0;
}

bool stoneGiant(Player *player1, Player *player2)
{
    int wall;
    int castle;
    
    wall = player2->getWall();
    castle = player2->getCastle();
    player1->setWall(player1->getWall() + 4);
    if (wall > 10)
    {
        castle -= 10 - wall;
        if (castle < 0)
            castle = 0;
    }
    else
    {
        wall -= 10;
    }
    player2->setWall(wall);
    player2->setCastle(castle);
    
    return 0;
}

bool sheepishRabbit(Player *player1, Player *player2)
{
    int wall;
    int castle;
    
    wall = player2->getWall();
    castle = player2->getCastle();
    player2->setCrystals(player1->getCrystals() - 3);
    if (wall > 6)
    {
        castle -= 6 - wall;
        if (castle < 0)
            castle = 0;
    }
    else
    {
        wall -= 6;
    }
    player2->setWall(wall);
    player2->setCastle(castle);
    
    return 0;
}

bool rubyWand(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 5);
    
    return 0;
}

bool rockSlasher(Player *player1, Player *player2)
{
    int wall;
    int castle;
    
    wall = player2->getWall();
    castle = player2->getCastle();
    if (wall > 6)
    {
        castle -= 6 - wall;
        if (castle < 0)
            castle = 0;
    }
    else
    {
        wall -= 6;
    }
    player2->setWall(wall);
    player2->setCastle(castle);
    
    return 0;
}

bool recycledRainbows(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 1);
    player2->setCastle(player2->getCastle() + 1);
    player1->setCrystals(player1->getCrystals() + 3);
    
    return 0;
}

bool protectionWard(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 8);
    player1->setWall(player2->getWall() + 3);
    
    return 0;
}

bool mortarMole(Player *player1, Player *player2)
{
    int castle;
    
    castle = player2->getCastle();
    castle -= 4;
    if (castle < 0)
        castle = 0;
    player2->setCastle(castle);
    
    return 0;
}

bool mobbinGoblin(Player *player1, Player *player2)
{
    int p1wall;
    int p1castle;
    int p2wall;
    int p2castle;
    
    p1wall = player1->getWall();
    p1castle = player1->getCastle();
    if (p1wall > 3)
    {
        p1castle -= 3 - p1wall;
        if (p1castle < 0)
            p1castle = 0;
    }
    else
    {
        p1wall -= 3;
    }
    player1->setWall(p1wall);
    player1->setCastle(p1castle);
    
    p2wall = player2->getWall();
    p2castle = player2->getCastle();
    if (p2wall > 6)
    {
        p2castle -= 6 - p2wall;
        if (p2castle < 0)
            p2castle = 0;
    }
    else
    {
        p2wall -= 6;
    }
    player2->setWall(p2wall);
    player2->setCastle(p2castle);
    
    return 0;
}

bool manaStomper(Player *player1, Player *player2)
{
    int wall;
    int castle;
    int magic;
    
    wall = player2->getWall();
    castle = player2->getCastle();
    magic = player2->getMagic();
    if (wall > 8)
    {
        castle -= 8 - wall;
        if (castle < 0)
            castle = 0;
    }
    else
    {
        wall -= 8;
    }
    magic -= 1;
    if (magic < 0)
        magic = 0;
    player2->setWall(wall);
    player2->setCastle(castle);
    player2->setMagic(magic);
    
    return 0;
}

bool manaDisease(Player *player1, Player *player2)
{
    int p1Gems;
    int p2Gems;
    
    p1Gems = player1->getCrystals();
    p2Gems = player2->getCrystals();
    p1Gems -= 8;
    p2Gems -= 8;
    
    if (p1Gems < 0)
        p1Gems = 0;
    if (p2Gems < 0)
        p2Gems = 0;
    player1->setCrystals(p1Gems);
    player2->setCrystals(p2Gems);
    
    return 0;
}

bool magicMiners(Player *player1, Player *player2)
{
    player1->setWall(player1->getWall() + 4);
    player1->setMagic(player1->getMagic() + 4);
    
    return 0;
}

bool instantWall(Player *player1, Player *player2)
{
    player1->setWall(player1->getWall() + 3);
    
    return 0;
}

bool insecureWall(Player *player1, Player *player2)
{
    player1->setWall(player1->getWall() + 4);
    
    return 0;
}

bool harmonicOrc(Player *player1, Player *player2)
{
    player1->setWall(player1->getWall() + 6);
    player1->setCastle(player1->getCastle() + 7);
    
    return 0;
}

bool friendship(Player *player1, Player *player2)
{
    player1->setWall(player1->getWall() + 1);
    
    return 1;
}

bool flyinGoblin(Player *player1, Player *player2)
{
    int wall;
    int castle;
    
    wall = player2->getWall();
    castle = player2->getCastle();
    if (wall > 2)
    {
        castle -= 2 - wall;
        if (castle < 0)
            castle = 0;
    }
    else
    {
        wall -= 2;
    }
    player2->setWall(wall);
    player2->setCastle(castle);
    
    return 1;
}

bool emeraldWand(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 8);
    
    return 0;
}

bool clubbinGoblin(Player *player1, Player *player2)
{
    int p1castle;
    int p2wall;
    int p2castle;
    
    p1castle = player1->getCastle();
    p1castle -= 3;
    if (p1castle < 0)
        p1castle = 0;
    player1->setCastle(p1castle);
    
    p2wall = player2->getWall();
    p2castle = player2->getCastle();
    if (p2wall > 8)
    {
        p2castle -= 8 - p2wall;
        if (p2castle < 0)
            p2castle = 0;
    }
    else
    {
        p2wall -= 8;
    }
    player2->setWall(p2wall);
    player2->setCastle(p2castle);
    
    return 0;
}

bool bowminGoblin(Player *player1, Player *player2)
{
    int p1wall;
    int p1castle;
    int p2castle;

    p1wall = player1->getWall();
    p1castle = player1->getCastle();
    if (p1wall > 1)
    {
        p1castle -= 1 - p1wall;
        if (p1castle < 0)
            p1castle = 0;
            }
    else
    {
        p1wall -= 1;
    }
    player1->setWall(p1wall);
    player1->setCastle(p1castle);

    p2castle = player2->getCastle();
    p2castle -= 3;
    if (p2castle < 0)
        p2castle = 0;
    player2->setCastle(p2castle);

    return 0;
}

bool bottledFlatulence(Player *player1, Player *player2)
{
    int castle;
    
    castle = player2->getCastle();
    castle -= 3;
    if (castle < 0)
        castle = 0;
    player2->setCastle(castle);
    
    return 0;
}

bool amethystWand(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 3);
    
    return 0;
}