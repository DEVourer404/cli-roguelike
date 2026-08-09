#include "Item.h"

Item::Item(std::string  id, std::string  name, char symbol):
id_(std::move(id)), name_(std::move(name)), symbol(symbol), is_picked_(false) {}

char Item::get_symbol() const { return symbol; }
const std::string &Item::get_name() const { return name_; }
const std::string &Item::get_id() const { return id_;  }
Vec2 &Item::get_item_pos() { return item_pos_; }


