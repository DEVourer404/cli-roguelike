#include "Consumable.h"

Consumable::Consumable(std::string id, std::string name, int amount):
Item(std::move(id), std::move(name), '!'), amount_(amount) {}

int Consumable::get_amount() const { return amount_; }

