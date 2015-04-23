//
//  File.cpp
//  castlewars
//
//  Created by admin on 3/17/15.
//
//

#include "Card.h"

Card::Card(SRes::ptrfunc effect, int cost, char *image)
{
    this->effect = effect;
    this->cost = cost;
    this->image = image;
}

const int Card::getCost()
{
    return this->cost;
}

const SRes::ptrfunc Card::getEffect()
{
    return this->effect;
}

const char *Card::getImage()
{
    return this->image;
}

void Card::damageCastle(Player *player, int damage)
{
    printf("        %s's castle takes %d dmg\n", player->getName(), damage);
    player->addCastle(-damage);
}


void Card::damage(Player *player, int damage) {
    printf("        %s takes %d dmg\n", player->getName(), damage);
    int wall = player->getWall();
    int wallDmg = (wall >= damage ? damage : wall);
    player->addWall(-wallDmg);
    if (damage - wallDmg > 0) player->addCastle(-(damage - wallDmg));
}


SRes::playResults Card::getCardReport(bool success, bool extraTurn,
                                      int pGemMod, int pMagMod, int pCastleMod, int pWallMod,
                                      int oppGemMod, int oppMagMod, int oppCastleMod, int oppWallMod) {
    SRes::playResults report;
    report.success = success;
    report.extraTurn = extraTurn;
    report.pGemMod = pGemMod;
    report.pMagMod = pMagMod;
    report.pCastleMod = pCastleMod;
    report.pWallMod = pWallMod;
    report.oppGemMod = oppGemMod;
    report.oppMagMod = oppMagMod;
    report.oppCastleMod = oppCastleMod;
    report.oppWallMod = oppWallMod;
    
    return report;
}

SRes::playResults Card::stripMining() {
    return getCardReport(true, false,
                         5, -1, 0, 10,
                         0, 0, 0, 0);
}

SRes::playResults Card::stoneGiant() {
    return getCardReport(true, false,
                         0, 0, 0, 4,
                         0, 0, 0, -10);
}

SRes::playResults Card::sheepishRabbit() {
    return getCardReport(true, false,
                         5, 0, 0, 0,
                         -3, 0, 0, -6);
}

SRes::playResults Card::rubyWand() {
    return getCardReport(true, false,
                         0, 0, 5, 0,
                         0, 0, 0, 0);
}

SRes::playResults Card::rockSlasher() {
    return getCardReport(true, false,
                         0, 0, 0, 0,
                         0, 0, 0, -6);
}

SRes::playResults Card::recycledRainbows()
{
    return getCardReport(true, false,
                         3, 0, 1, 0,
                         0, 0, 1, 0);
}

SRes::playResults Card::protectionWard()
{
    return getCardReport(true, false,
                         0, 0, 8, 3,
                         0, 0, 0, 0);
}

SRes::playResults Card::mortarMole() {
    return getCardReport(true, false,
                         0, 0, 0, 0,
                         0, 0, 0, -4);
}

SRes::playResults Card::mobbinGoblin() {
    return getCardReport(true, false,
                         0, 0, 0, -3,
                         0, 0, 0, -6);
}

SRes::playResults Card::manaStompers() {
    return getCardReport(true, false,
                         0, 0, 0, 0,
                         0, -1, 0, -8);
}

SRes::playResults Card::manaDisease() {
    return getCardReport(true, false,
                         -8, 0, 0, 0,
                         -8, 0, 0, 0);
}

SRes::playResults Card::magicMiners() {
    return getCardReport(true, false,
                         0, 1, 0, 4,
                         0, 0, 0, 0);
}

SRes::playResults Card::instantWall() {
    return getCardReport(true, false,
                         0, 0, 0, 3,
                         0, 0, 0, 0);
}

SRes::playResults Card::insecureWall() {
    return getCardReport(true, false,
                         0, 0, 0, 4,
                         0, 0, 0, 0);
}

SRes::playResults Card::harmonicOrc() {
    return getCardReport(true, false,
                         0, 0, 3, 6,
                         0, 0, 0, 0);
}

SRes::playResults Card::friendship() {
    return getCardReport(true, true,
                         0, 0, 0, 1,
                         0, 0, 0, 0);
}

SRes::playResults Card::flyinGoblin() {
    return getCardReport(true, true,
                         0, 0, 0, 0,
                         0, 0, 0, -2);
}

SRes::playResults Card::emeraldWand() {
    return getCardReport(true, false,
                         0, 0, 8, 0,
                         0, 0, 0, 0);
}

SRes::playResults Card::clubbinGoblin() {
    return getCardReport(true, false,
                         0, 0, -3, 0,
                         0, 0, 0, -8);
}

SRes::playResults Card::bowminGoblin() {
    return getCardReport(true, false,
                         0, 0, 0, -1,
                         0, 0, -3, 0);
}

SRes::playResults Card::bottledFlatulence() {
    return getCardReport(true, false,
                         0, 0, 0, 0,
                         0, 0, -3, 0);
}

SRes::playResults Card::amethystWand() {
    return getCardReport(true, false,
                         0, 0, 3, 0,
                         0, 0, 0, 0);
}

std::vector<Card *> *Card::getNewDeck()
{
    std::vector<Card *> *deck = new std::vector<Card *>();

    deck->push_back(new Card(&Card::amethystWand, 4, "amethyst_wand.png"));
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
    deck->push_back(new Card(&mortarMole, 6, "mortar_mole.png"));
    deck->push_back(new Card(&protectionWard, 12, "protection_ward.png"));
    deck->push_back(new Card(&recycledRainbows, 0, "recycled_rainbow.png"));
    deck->push_back(new Card(&rockSlasher, 5, "rock_slasher.png"));
    deck->push_back(new Card(&rubyWand, 6, "ruby_wand.png"));
    deck->push_back(new Card(&sheepishRabbit, 9, "sheepish_rabbit.png"));
    deck->push_back(new Card(&stoneGiant, 12, "stone_giant.png"));
    deck->push_back(new Card(&stripMining, 0, "strip_mining.png"));
    
    return deck;
}