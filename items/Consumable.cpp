#include "Consumable.h"

Consumable::Consumable(std::string id, std::string name, int amount):
Item(std::move(id), std::move(name), '!'), amount_(amount) {}

std::unique_ptr<Item> Consumable::clone() const {
    return std::make_unique<Consumable>(*this);
}

int Consumable::get_amount() const { return amount_; }

