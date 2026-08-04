#include "Item.h"

Item::Item(std::string  id, std::string  name, char symbol):
id_(std::move(id)), name_(std::move(name)), symbol(symbol) {}

char Item::get_symbol() const { return symbol; }
const std::string &Item::get_name() const { return name_; }
const std::string &Item::get_id() const { return id_;  }


