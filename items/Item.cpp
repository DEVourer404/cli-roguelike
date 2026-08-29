#include "Item.h"

Item::Item(std::string  id, std::string  name, char symbol, int price):
id_(std::move(id)), name_(std::move(name)), symbol(symbol), price_(price), is_picked_(false), is_sellable_(false) {}

char Item::get_symbol() const { return symbol; }
const std::string &Item::get_name() const { return name_; }
const std::string &Item::get_id() const { return id_;  }
int Item::get_price() const { return price_; }
Vec2 &Item::get_item_pos() { return item_pos_; }
bool Item::is_picked() const { return is_picked_; }
bool Item::is_sellable() const { return is_sellable_; }
void Item::set_picked(bool value) { is_picked_ = value; }
void Item::set_sellable(bool value) { is_sellable_ = value; }



