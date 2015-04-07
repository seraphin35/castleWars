//
//  File.cpp
//  castlewars
//
//  Created by admin on 3/17/15.
//
//

#include "Card.h"

Card::Card(ptrfunc effect, int value, cocos2d::CCSprite* image)
{
    this->effect = effect;
    this->value = value;
}

const int Card::getValue()
{
    return this->value;
}

const ptrfunc Card::getEffect()
{
    return this->effect;
}

const cocos2d::CCSprite* Card::getImage()
{
    return this->image;
}

void Card::damageCastle(Player *player, int damage)
{
    int castle = player->getCastle();
    
    castle -= damage;
    player->setCastle(castle);
}


void Card::damage(Player *player, int damage) {
    int wall = player->getWall();
    
    wall -= damage;
    if (wall <= 0) {
        damageCastle(player, -wall);
    }
    player->setWall(wall);
}

bool Card::stripMining(Player *player1, Player *player2)
{
    int magic = player1->getMagic();
    
    magic -= 1;
    if (magic < 0)
        magic = 0;
    player1->setMagic(magic);
    player1->setWall(player1->getWall() + 10);
    player1->setCrystals(player1->getCrystals() + 5);
    
    return false;
}

bool Card::stoneGiant(Player *player1, Player *player2)
{
    damage(player2, 10);
    player1->setWall(player1->getWall() + 4);
    
    return false;
}

bool Card::sheepishRabbit(Player *player1, Player *player2)
{
    damage(player2, 6);
    player2->setCrystals(player1->getCrystals() - 3);
    
    return false;
}

bool Card::rubyWand(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 5);
    
    return false;
}

bool Card::rockSlasher(Player *player1, Player *player2)
{
    damage(player2, 6);
    
    return false;
}

bool Card::recycledRainbows(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 1);
    player2->setCastle(player2->getCastle() + 1);
    player1->setCrystals(player1->getCrystals() + 3);
    
    return false;
}

bool Card::protectionWard(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 8);
    player1->setWall(player2->getWall() + 3);
    
    return false;
}

bool Card::mortarMole(Player *player1, Player *player2)
{
    damageCastle(player2, 4);
    
    return false;
}

bool Card::mobbinGoblin(Player *player1, Player *player2)
{
    damage(player1, 3);
    damage(player2, 6);
    
    return false;
}

bool Card::manaStompers(Player *player1, Player *player2)
{
    int magic;
    
    damage(player2, 8);
    magic -= 1;
    if (magic < 0)
        magic = 0;
    player2->setMagic(magic);
    
    return false;
}

bool Card::manaDisease(Player *player1, Player *player2)
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
    
    return false;
}

bool Card::magicMiners(Player *player1, Player *player2)
{
    player1->setWall(player1->getWall() + 4);
    player1->setMagic(player1->getMagic() + 4);
    
    return false;
}

bool Card::instantWall(Player *player1, Player *player2)
{
    player1->setWall(player1->getWall() + 3);
    
    return false;
}

bool Card::insecureWall(Player *player1, Player *player2)
{
    player1->setWall(player1->getWall() + 4);
    
    return false;
}

bool Card::harmonicOrc(Player *player1, Player *player2)
{
    player1->setWall(player1->getWall() + 6);
    player1->setCastle(player1->getCastle() + 7);
    
    return false;
}

bool Card::friendship(Player *player1, Player *player2)
{
    player1->setWall(player1->getWall() + 1);
    
    return true;
}

bool Card::flyinGoblin(Player *player1, Player *player2)
{
    damage(player2, 2);
    
    return true;
}

bool Card::emeraldWand(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 8);
    
    return false;
}

bool Card::clubbinGoblin(Player *player1, Player *player2)
{
    damageCastle(player1, 3);
    damage(player2, 8);
    
    return false;
}

bool Card::bowminGoblin(Player *player1, Player *player2)
{
    damageCastle(player2, 3);
    damage(player1, 1);
    
    return false;
}

bool Card::bottledFlatulence(Player *player1, Player *player2)
{
    damageCastle(player2, 3);
    
    return false;
}

bool Card::amethystWand(Player *player1, Player *player2)
{
    player1->setCastle(player1->getCastle() + 3);
    
    return false;
}

std::vector<Card *> &Card::getNewDeck()
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
    deck->push_back(new Card(&manaStompers, 11, cocos2d::CCSprite::create("mana_stompers.png")));
    deck->push_back(new Card(&mobbinGoblin, 3, cocos2d::CCSprite::create("mobbin_goblin.png")));
    deck->push_back(new Card(&mortarMole, 6, cocos2d::CCSprite::create("mortal_mole.png")));
    deck->push_back(new Card(&protectionWard, 12, cocos2d::CCSprite::create("protection_ward.png")));
    deck->push_back(new Card(&recycledRainbows, 0, cocos2d::CCSprite::create("recycled_rainbow.png")));
    deck->push_back(new Card(&rockSlasher, 5, cocos2d::CCSprite::create("rock_slasher.png")));
    deck->push_back(new Card(&rubyWand, 6, cocos2d::CCSprite::create("ruby_wand.png")));
    deck->push_back(new Card(&sheepishRabbit, 9, cocos2d::CCSprite::create("sheepish_rabbit.png")));
    deck->push_back(new Card(&stoneGiant, 12, cocos2d::CCSprite::create("stone_giant.png")));
    deck->push_back(new Card(&stripMining, 0, cocos2d::CCSprite::create("strip_mining.png")));
    
    return *deck;
}