//
//  StripMining.cpp
//  castlewars
//
//  Created by Guest User on 3/31/15.
//
//

#include "Card.h"
#include "Cards.h"

void damageAll(Player *player, int damage)
{
    int wall;
    int castle;
    
    wall = player->getWall();
    castle = player->getCastle();
    if (wall > damage)
    {
        castle -= damage - wall;
        if (castle < 0)
            castle = 0;
    }
    else
    {
        wall -= damage;
    }
    player->setWall(wall);
    player->setCastle(castle);
}

void damageCastle(Player *player, int damage)
{
    int castle;
    
    castle = player->getCastle();
    castle -= damage;
    if (castle < 0)
        castle = 0;
    player->setCastle(castle);
}

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
    damageAll(player2, 10);
    player1->setWall(player1->getWall() + 4);
    
    return 0;
}

bool sheepishRabbit(Player *player1, Player *player2)
{
    damageAll(player2, 6);
    player2->setCrystals(player1->getCrystals() - 3);
    
    return 0;
}

bool rubyWand(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 5);
    
    return 0;
}

bool rockSlasher(Player *player1, Player *player2)
{
    damageAll(player2, 6);
    
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
    damageCastle(player2, 4);
    
    return 0;
}

bool mobbinGoblin(Player *player1, Player *player2)
{
    damageAll(player1, 3);
    damageAll(player2, 6);
    
    return 0;
}

bool manaStomper(Player *player1, Player *player2)
{
    int magic;
    
    damageAll(player2, 8);
    magic -= 1;
    if (magic < 0)
        magic = 0;
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
    damageAll(player2, 2);
    
    return 1;
}

bool emeraldWand(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 8);
    
    return 0;
}

bool clubbinGoblin(Player *player1, Player *player2)
{
    damageCastle(player1, 3);
    damageAll(player2, 8);
    
    return 0;
}

bool bowminGoblin(Player *player1, Player *player2)
{
    damageCastle(player2, 3);
    damageAll(player1, 1);

    return 0;
}

bool bottledFlatulence(Player *player1, Player *player2)
{
    damageCastle(player2, 3);
    
    return 0;
}

bool amethystWand(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 3);
    
    return 0;
}

std::vector<Card *> &getDeck()
{
    std::vector<Card *> *deck = new std::vector<Card *>();
    deck->push_back(new Card(&amethystWand, 4, cocos2d::CCSprite::create("amethyst_wand.png")));
    deck->push_back(new Card(&bottledFlatulence, 4, cocos2d::CCSprite::create("bottled_flatulence.png")));
    deck->push_back(new Card(&bowminGoblin, 4, cocos2d::CCSprite::create("bowmin_goblin.png")));
    deck->push_back(new Card(&clubbinGoblin, 4, cocos2d::CCSprite::create("clubin_goblin.png")));
    deck->push_back(new Card(&emeraldWand, 10, cocos2d::CCSprite::create("emerald_wand.png")));
    deck->push_back(new Card(&flyinGoblin, 3, cocos2d::CCSprite::create("flyin_goblin.png")));
    deck->push_back(new Card(&friendship, 2, cocos2d::CCSprite::create("friendship.png")));
    deck->push_back(new Card(&harmonicOrc, 7, cocos2d::CCSprite::create("harmonic_orc.png")));
    deck->push_back(new Card(&insecureWall, 3, cocos2d::CCSprite::create("insecure_wall.png")));
    deck->push_back(new Card(&instantWall, 2, cocos2d::CCSprite::create("instant_wall.png")));
    deck->push_back(new Card(&magicMiners, 4, cocos2d::CCSprite::create("magic_miners.png")));
    deck->push_back(new Card(&manaDisease, 0, cocos2d::CCSprite::create("mana_disease.png")));
    deck->push_back(new Card(&manaStomper, 11, cocos2d::CCSprite::create("mana_stompers.png")));
    deck->push_back(new Card(&mobbinGoblin, 3, cocos2d::CCSprite::create("mobbin_goblin.png")));
    deck->push_back(new Card(&mortarMole, 6, cocos2d::CCSprite::create("mortal_mole.png")));
    deck->push_back(new Card(&protectionWard, 12, cocos2d::CCSprite::create("protection_ward.png")));
    deck->push_back(new Card(&recycledRainbows, 0, cocos2d::CCSprite::create("recycled_rainbow.png")));
    deck->push_back(new Card(&rockSlasher, 5, cocos2d::CCSprite::create("rock_slasher.png")));
    deck->push_back(new Card(&rubyWand, 6, cocos2d::CCSprite::create("ruby_wand.png")));
    deck->push_back(new Card(&sheepishRabbit, 9, cocos2d::CCSprite::create("sheepish_rabbit.png")));
    deck->push_back(new Card(&stoneGiant, 12, cocos2d::CCSprite::create("stone_giant.png")));
    deck->push_back(new Card(&stripMining, 0, cocos2d::CCSprite::create("strip_mining.png")));
    
    return (*deck);
}