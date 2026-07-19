#include "Entity.h"

Entity::Entity(const std::string& name, int health, char entity_symbol):
name_(name), health_(health), entity_symbol_(entity_symbol)  {}

const Vec2 &Entity::get_entity_pos() const{
    return entity_pos;
}

Vec2& Entity::get_entity_pos() {
    return entity_pos;
}

char Entity::get_entity_symbol() {
    return entity_symbol_;
}
