//
//  File.cpp
//  castlewars
//
//  Created by admin on 3/17/15.
//
//

#include "Card.h"

Card::Card(ptrfunc effect, int cost, char *image)
{
    this->effect = effect;
    this->cost = cost;
    this->image = image;
}

const int Card::getCost()
{
    return this->cost;
}

const ptrfunc Card::getEffect()
{
    return this->effect;
}

const char *Card::getImage()
{
    return this->image;
}

void Card::damageCastle(Player *player, int damage)
{
    player->removeCastle(damage);
}


void Card::damage(Player *player, int damage) {
    int wall = player->getWall();
    int wallDmg = (wall >= damage ? damage : wall);
    player->removeWall(wallDmg);
    if (damage - wallDmg > 0) player->removeCastle(damage - wallDmg);
}

bool Card::stripMining(Player *player1, Player *player2)
{
    player1->removeMagic(1);
    player1->addWall(10);
    player1->addGems(5);
    
    return false;
}

bool Card::stoneGiant(Player *player1, Player *player2)
{
    player1->addWall(4);
    damage(player2, 10);
    
    return false;
}

bool Card::sheepishRabbit(Player *player1, Player *player2)
{
    damage(player2, 6);
    player2->removeGems(3);
    
    return false;
}

bool Card::rubyWand(Player *player1, Player *player2)
{
    player1->addCastle(5);
    
    return false;
}

bool Card::rockSlasher(Player *player1, Player *player2)
{
    damage(player2, 6);
    
    return false;
}

bool Card::recycledRainbows(Player *player1, Player *player2)
{
    player1->addCastle(1);
    player2->addCastle(1);
    player1->addGems(3);
    
    return false;
}

bool Card::protectionWard(Player *player1, Player *player2)
{
    player1->addCastle(8);
    player1->addWall(3);
    
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
    damage(player2, 8);
    player2->removeMagic(1);
    
    return false;
}

bool Card::manaDisease(Player *player1, Player *player2)
{
    player1->removeGems(8);
    player2->removeGems(8);
    
    return false;
}

bool Card::magicMiners(Player *player1, Player *player2)
{
    player1->addWall(4);
    player1->addMagic(1);
    
    return false;
}

bool Card::instantWall(Player *player1, Player *player2)
{
    player1->addWall(3);
    
    return false;
}

bool Card::insecureWall(Player *player1, Player *player2)
{
    player1->addWall(4);
    
    return false;
}

bool Card::harmonicOrc(Player *player1, Player *player2)
{
    player1->addWall(6);
    player1->addCastle(3);
    
    return false;
}

bool Card::friendship(Player *player1, Player *player2)
{
    player1->addWall(1);
    
    return true;
}

bool Card::flyinGoblin(Player *player1, Player *player2)
{
    damage(player2, 2);
    
    return true;
}

bool Card::emeraldWand(Player *player1, Player *player2)
{
    player1->addCastle(8);
    
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
    damage(player1, 1);
    damageCastle(player2, 3);
    
    return false;
}

bool Card::bottledFlatulence(Player *player1, Player *player2)
{
    damageCastle(player2, 3);
    
    return false;
}

bool Card::amethystWand(Player *player1, Player *player2)
{
    player1->addCastle(3);
    
    return false;
}

std::vector<Card *> *Card::getNewDeck()
{
    std::vector<Card *> *deck = new std::vector<Card *>();
    
    deck->push_back(new Card(&amethystWand, 4, "amethyst_wand.png"));
    deck->push_back(new Card(&bottledFlatulence, 4, "bottled_flatulence.png"));
    deck->push_back(new Card(&bowminGoblin, 4, "bowmin_goblin.png"));
    deck->push_back(new Card(&clubbinGoblin, 4, "clubin_goblin.png"));
    deck->push_back(new Card(&emeraldWand, 10, "emerald_wand.png"));
    deck->push_back(new Card(&flyinGoblin, 3, "flyin_goblin.png"));
    deck->push_back(new Card(&friendship, 2, "friendship.png"));
    deck->push_back(new Card(&harmonicOrc, 7, "harmonic_orc.png"));
    deck->push_back(new Card(&insecureWall, 3, "insecure_wall.png"));
    deck->push_back(new Card(&instantWall, 2, "instant_wall.png"));
    deck->push_back(new Card(&magicMiners, 4, "magic_miners.png"));
    deck->push_back(new Card(&manaDisease, 0, "mana_disease.png"));
    deck->push_back(new Card(&manaStompers, 11, "mana_stompers.png"));
    deck->push_back(new Card(&mobbinGoblin, 3, "mobbin_goblin.png"));
    deck->push_back(new Card(&mortarMole, 6, "mortal_mole.png"));
    deck->push_back(new Card(&protectionWard, 12, "protection_ward.png"));
    deck->push_back(new Card(&recycledRainbows, 0, "recycled_rainbow.png"));
    deck->push_back(new Card(&rockSlasher, 5, "rock_slasher.png"));
    deck->push_back(new Card(&rubyWand, 6, "ruby_wand.png"));
    deck->push_back(new Card(&sheepishRabbit, 9, "sheepish_rabbit.png"));
    deck->push_back(new Card(&stoneGiant, 12, "stone_giant.png"));
    deck->push_back(new Card(&stripMining, 0, "strip_mining.png"));
    
    return deck;
}