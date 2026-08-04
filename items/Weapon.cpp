#include "Weapon.h"

#include <utility>

Weapon::Weapon(std::string id, std::string name, int damage):
Item(std::move(id), std::move(name), '/'), damage_(damage) {}

std::unique_ptr<Item> Weapon::clone() const {
    return std::make_unique<Weapon>(*this);
}

int Weapon::get_damage() const { return damage_; }
