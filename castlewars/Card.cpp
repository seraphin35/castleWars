//
//  File.cpp
//  castlewars
//
//  Created by admin on 3/17/15.
//
//

#include "Card.h"

Card::Card(SRes::ResID resID, SRes::ptrfunc effect, int cost, char *image)
{
    this->id = resID;
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

const SRes::ResID   Card::getID() {
    return this->id;
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


SRes::playResults Card::getCardReport(bool success, bool extraTurn, SRes::ResID id,
                                      int pGemMod, int pMagMod, int pCastleMod, int pWallMod,
                                      int oppGemMod, int oppMagMod, int oppCastleMod, int oppWallMod) {
    SRes::playResults report;
    report.success = success;
    report.extraTurn = extraTurn;
    report.cardID = id;
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
    return getCardReport(true, false, SRes::STRIP_MINING,
                         5, -1, 0, 10,
                         0, 0, 0, 0);
}

SRes::playResults Card::stoneGiant() {
    return getCardReport(true, false, SRes::STONE_GIANT,
                         0, 0, 0, 4,
                         0, 0, 0, -10);
}

SRes::playResults Card::sheepishRabbit() {
    return getCardReport(true, false, SRes::SHEEPISH_RABBIT,
                         0, 0, 0, 0,
                         -3, 0, 0, -6);
}

SRes::playResults Card::rubyWand() {
    return getCardReport(true, false, SRes::RUBY_WAND,
                         0, 0, 5, 0,
                         0, 0, 0, 0);
}

SRes::playResults Card::rockSlasher() {
    return getCardReport(true, false, SRes::ROCK_SLASHER,
                         0, 0, 0, 0,
                         0, 0, 0, -6);
}

SRes::playResults Card::recycledRainbows()
{
    return getCardReport(true, false, SRes::RECYCLED_RAINBOW,
                         3, 0, 1, 0,
                         0, 0, 1, 0);
}

SRes::playResults Card::protectionWard()
{
    return getCardReport(true, false, SRes::PROTECTION_WARD,
                         0, 0, 8, 3,
                         0, 0, 0, 0);
}

SRes::playResults Card::mortarMole() {
    return getCardReport(true, false, SRes::MORTAR_MOLE,
                         0, 0, 0, 0,
                         0, 0, 0, -4);
}

SRes::playResults Card::mobbinGoblin() {
    return getCardReport(true, false, SRes::MOBBIN_GOBLIN,
                         0, 0, 0, -3,
                         0, 0, 0, -6);
}

SRes::playResults Card::manaStompers() {
    return getCardReport(true, false, SRes::MANA_STOMPERS,
                         0, 0, 0, 0,
                         0, -1, 0, -8);
}

SRes::playResults Card::manaDisease() {
    return getCardReport(true, false, SRes::MANA_DISEASE,
                         -8, 0, 0, 0,
                         -8, 0, 0, 0);
}

SRes::playResults Card::magicMiners() {
    return getCardReport(true, false, SRes::MAGIC_MINERS,
                         0, 1, 0, 4,
                         0, 0, 0, 0);
}

SRes::playResults Card::instantWall() {
    return getCardReport(true, false, SRes::INSTANT_WALL,
                         0, 0, 0, 3,
                         0, 0, 0, 0);
}

SRes::playResults Card::insecureWall() {
    return getCardReport(true, false, SRes::INSECURE_WALL,
                         0, 0, 0, 4,
                         0, 0, 0, 0);
}

SRes::playResults Card::harmonicOrc() {
    return getCardReport(true, false, SRes::HARMONIC_ORC,
                         0, 0, 3, 6,
                         0, 0, 0, 0);
}

SRes::playResults Card::friendship() {
    return getCardReport(true, true, SRes::FRIENDSHIP,
                         0, 0, 0, 1,
                         0, 0, 0, 0);
}

SRes::playResults Card::flyinGoblin() {
    return getCardReport(true, true, SRes::FLYIN_GOBLIN,
                         0, 0, 0, 0,
                         0, 0, 0, -2);
}

SRes::playResults Card::emeraldWand() {
    return getCardReport(true, false, SRes::EMERALD_WAND,
                         0, 0, 8, 0,
                         0, 0, 0, 0);
}

SRes::playResults Card::clubbinGoblin() {
    return getCardReport(true, false, SRes::CLUBIN_GOBLIN,
                         0, 0, -3, 0,
                         0, 0, 0, -8);
}

SRes::playResults Card::bowminGoblin() {
    return getCardReport(true, false, SRes::BOWMIN_GOBLIN,
                         0, 0, 0, -1,
                         0, 0, -3, 0);
}

SRes::playResults Card::bottledFlatulence() {
    return getCardReport(true, false, SRes::BOTTLED_FLATULENCE,
                         0, 0, 0, 0,
                         0, 0, -3, 0);
}

SRes::playResults Card::amethystWand() {
    return getCardReport(true, false, SRes::AMETHYST_WAND,
                         0, 0, 3, 0,
                         0, 0, 0, 0);
}

std::vector<Card *> *Card::getNewDeck()
{
    std::vector<Card *> *deck = new std::vector<Card *>();

    deck->push_back(new Card(SRes::AMETHYST_WAND, &Card::amethystWand, 4, "amethyst_wand.png"));
    deck->push_back(new Card(SRes::BOTTLED_FLATULENCE, &bottledFlatulence, 4, "bottled_flatulence.png"));
    deck->push_back(new Card(SRes::BOWMIN_GOBLIN, &bowminGoblin, 4, "bowmin_goblin.png"));
    deck->push_back(new Card(SRes::CLUBIN_GOBLIN, &clubbinGoblin, 4, "clubin_goblin.png"));
    deck->push_back(new Card(SRes::EMERALD_WAND, &emeraldWand, 10, "emerald_wand.png"));
    deck->push_back(new Card(SRes::FLYIN_GOBLIN, &flyinGoblin, 3, "flyin_goblin.png"));
    deck->push_back(new Card(SRes::FRIENDSHIP, &friendship, 2, "friendship.png"));
    deck->push_back(new Card(SRes::HARMONIC_ORC, &harmonicOrc, 7, "harmonic_orc.png"));
    deck->push_back(new Card(SRes::INSECURE_WALL, &insecureWall, 3, "insecure_wall.png"));
    deck->push_back(new Card(SRes::INSTANT_WALL, &instantWall, 2, "instant_wall.png"));
    deck->push_back(new Card(SRes::MAGIC_MINERS, &magicMiners, 4, "magic_miners.png"));
    deck->push_back(new Card(SRes::MANA_DISEASE, &manaDisease, 0, "mana_disease.png"));
    deck->push_back(new Card(SRes::MANA_STOMPERS, &manaStompers, 11, "mana_stompers.png"));
    deck->push_back(new Card(SRes::MOBBIN_GOBLIN, &mobbinGoblin, 3, "mobbin_goblin.png"));
    deck->push_back(new Card(SRes::MORTAR_MOLE, &mortarMole, 6, "mortar_mole.png"));
    deck->push_back(new Card(SRes::PROTECTION_WARD, &protectionWard, 12, "protection_ward.png"));
    deck->push_back(new Card(SRes::RECYCLED_RAINBOW, &recycledRainbows, 0, "recycled_rainbow.png"));
    deck->push_back(new Card(SRes::ROCK_SLASHER, &rockSlasher, 5, "rock_slasher.png"));
    deck->push_back(new Card(SRes::RUBY_WAND, &rubyWand, 6, "ruby_wand.png"));
    deck->push_back(new Card(SRes::SHEEPISH_RABBIT, &sheepishRabbit, 9, "sheepish_rabbit.png"));
    deck->push_back(new Card(SRes::STONE_GIANT, &stoneGiant, 12, "stone_giant.png"));
    deck->push_back(new Card(SRes::STRIP_MINING, &stripMining, 0, "strip_mining.png"));
    
    return deck;
}