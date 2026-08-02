#include "Armor.h"
#include <utility>

Armor::Armor(std::string id, std::string name, int armor_rate):
Item(std::move(id), std::move(name), '['), armor_rate_(armor_rate){}

int Armor::get_armor_rate() const { return armor_rate_; }

