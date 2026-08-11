#include "Consumable.h"
#include "../entities/Player.h"

Consumable::Consumable(std::string id, std::string name, int amount):
Item(std::move(id), std::move(name), '!'), amount_(amount) {}

std::unique_ptr<Item> Consumable::clone() const {
    return std::make_unique<Consumable>(*this);
}

void Consumable::use(Player& player) {
    player.modify_health(amount_);
    player.remove_from_inventory(this);
}

int Consumable::get_amount() const { return amount_; }

