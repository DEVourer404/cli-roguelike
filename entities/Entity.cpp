#include "Entity.h"

Entity::Entity(const std::string& name, char entity_symbol):
name_(name), current_health_(0), entity_symbol_(entity_symbol) {}

const Vec2 &Entity::get_entity_pos() const{
    return entity_pos_;
}

Vec2& Entity::get_entity_pos() {
    return entity_pos_;
}

char Entity::get_entity_symbol() const {
    return entity_symbol_;
}

bool Entity::isAlive() const {
    return (current_health_ > 0);
}

int Entity::get_current_health() const {
    return current_health_;
}

const std::string& Entity::get_name() const {
    return name_;
}


void Entity::modify_health(int value)  {
    current_health_ += value;
    if(current_health_ < 0) current_health_ = 0;
    if(current_health_ > get_max_health()) current_health_ = get_max_health();
}
