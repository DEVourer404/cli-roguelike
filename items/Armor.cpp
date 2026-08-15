#include "Armor.h"
#include "entities/Player.h"
#include <utility>

Armor::Armor(std::string id, std::string name, int armor_rate):
Item(std::move(id), std::move(name), '['), armor_rate_(armor_rate){}

std::unique_ptr<Item> Armor::clone() const {
    return std::make_unique<Armor>(*this);
}

void Armor::use(Player& player) {
    player.equip_armor(this);
}

int Armor::get_armor_rate() const { return armor_rate_; }

